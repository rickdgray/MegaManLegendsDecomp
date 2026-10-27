<#
.SYNOPSIS
  Estimates MIPS function counts per file by scanning for common instruction patterns.
.DESCRIPTION
  Scans every file under -Path for two 4-byte-aligned MIPS patterns:
    jr ra               (0x03E00008)  function returns; roughly one per function
    addiu sp, sp, -N    (0x27BD8000+) stack-frame setup; roughly one per non-leaf function
  Files with code show dense hits. Asset files show none or near-zero.
.EXAMPLE
  .\tools\Count-MipsFunctions.ps1 -Path .\disc\extracted
.EXAMPLE
  .\tools\Count-MipsFunctions.ps1 -Path .\disc\extracted -CsvPath .\notes\function-counts.csv
#>
param(
    [Parameter(Mandatory)] [string] $Path,
    [string] $CsvPath
)

# Written for C# 5 so it compiles in both Windows PowerShell 5.1 and PowerShell 7.
if (-not ([System.Management.Automation.PSTypeName]'MipsScan').Type) {
    Add-Type -TypeDefinition @"
using System.IO;

public static class MipsScan
{
    // Returns { jrRaCount, prologueCount }.
    public static long[] Scan(string path)
    {
        byte[] d = File.ReadAllBytes(path);
        long jrRa = 0, prologues = 0;
        for (int i = 0; i + 3 < d.Length; i += 4)
        {
            uint w = (uint)d[i] | ((uint)d[i + 1] << 8) | ((uint)d[i + 2] << 16) | ((uint)d[i + 3] << 24);
            if (w == 0x03E00008u) jrRa++;                               // jr ra
            else if ((w & 0xFFFF8000u) == 0x27BD8000u) prologues++;     // addiu sp, sp, -N
        }
        return new long[] { jrRa, prologues };
    }
}
"@
}

$root = (Resolve-Path -LiteralPath $Path).Path

$results = Get-ChildItem -LiteralPath $root -Recurse -File | ForEach-Object {
    $r = [MipsScan]::Scan($_.FullName)
    $sizeKB = [math]::Round($_.Length / 1KB, 1)
    [pscustomobject]@{
        File        = $_.FullName.Substring($root.Length).TrimStart('\', '/')
        SizeKB      = $sizeKB
        JrRa        = $r[0]
        Prologues   = $r[1]
        JrRaPer100K = if ($_.Length -gt 0) { [math]::Round($r[0] / ($_.Length / 100KB), 1) } else { 0 }
    }
}

$withCode = $results | Where-Object { $_.JrRa -gt 0 } | Sort-Object JrRa -Descending
$withCode | Format-Table -AutoSize

"{0} of {1} files contain jr ra. Totals: {2} jr ra, {3} stack-frame prologues." -f `
    @($withCode).Count, @($results).Count,
    ($results | Measure-Object JrRa -Sum).Sum,
    ($results | Measure-Object Prologues -Sum).Sum

if ($CsvPath) {
    $results | Sort-Object JrRa -Descending | Export-Csv -LiteralPath $CsvPath -NoTypeInformation
    "Full results written to $CsvPath"
}