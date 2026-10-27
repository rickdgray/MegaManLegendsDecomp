<#
.SYNOPSIS
  Compares a mkpsxiso-rebuilt image against the original Redump Track 1.
.EXAMPLE
  .\tools\Compare-Track1.ps1 `
    -Original "disc\image\Mega Man Legends (USA) (Track 1).bin" `
    -Rebuilt  "disc\rebuild\mml.bin"
#>
param(
    [Parameter(Mandatory)] [string] $Original,
    [Parameter(Mandatory)] [string] $Rebuilt,
    [int] $MaxLines = 30
)

# Written for C# 5 so it compiles in both Windows PowerShell 5.1 and PowerShell 7.
if (-not ([System.Management.Automation.PSTypeName]'SectorDiff').Type) {
    Add-Type -TypeDefinition @"
using System;
using System.Collections.Generic;
using System.IO;
using System.Security.Cryptography;

public static class SectorDiff
{
    const int SectorSize = 2352;

    static int ReadFull(Stream s, byte[] buf)
    {
        int total = 0;
        while (total < buf.Length)
        {
            int n = s.Read(buf, total, buf.Length - total);
            if (n <= 0) break;
            total += n;
        }
        return total;
    }

    // SHA-1 of only the first 'length' bytes of a file.
    public static string Sha1Prefix(string path, long length)
    {
        using (var fs = File.OpenRead(path))
        using (var sha = SHA1.Create())
        {
            var buf = new byte[1 << 20];
            long left = length;
            while (left > 0)
            {
                int n = fs.Read(buf, 0, (int)Math.Min(buf.Length, left));
                if (n <= 0) break;
                sha.TransformBlock(buf, 0, n, null, 0);
                left -= n;
            }
            sha.TransformFinalBlock(new byte[0], 0, 0);
            return BitConverter.ToString(sha.Hash).Replace("-", "").ToLowerInvariant();
        }
    }

    // Region names assume a Mode 2 Form 1 layout; see notes in the chat for Form 2 sectors.
    static string Region(int b)
    {
        if (b < 16) return "header";
        if (b < 24) return "subheader";
        if (b < 2072) return "data";
        return "edc/ecc";
    }

    public static string[] Diff(string original, string rebuilt, int maxLines)
    {
        var lines = new List<string>();
        long compared = 0, diffSectors = 0, diffBytes = 0;

        using (var fa = File.OpenRead(original))
        using (var fb = File.OpenRead(rebuilt))
        {
            var a = new byte[SectorSize];
            var b = new byte[SectorSize];
            long total = fa.Length / SectorSize;

            for (long s = 0; s < total; s++)
            {
                int na = ReadFull(fa, a);
                int nb = ReadFull(fb, b);
                if (nb < na)
                {
                    lines.Add(string.Format("Rebuilt image ends early, at sector {0}", s));
                    break;
                }

                int count = 0, lo = -1, hi = -1;
                var regions = new HashSet<string>();
                for (int i = 0; i < na; i++)
                {
                    if (a[i] != b[i])
                    {
                        count++;
                        if (lo < 0) lo = i;
                        hi = i;
                        regions.Add(Region(i));
                    }
                }

                compared++;
                if (count > 0)
                {
                    diffSectors++;
                    diffBytes += count;
                    if (lines.Count < maxLines)
                        lines.Add(string.Format("sector {0}: {1} bytes, offsets {2}-{3} [{4}]",
                            s, count, lo, hi, string.Join(",", regions)));
                }
            }
        }

        lines.Insert(0, string.Format("{0} sectors compared, {1} differ, {2} bytes differ",
            compared, diffSectors, diffBytes));
        return lines.ToArray();
    }
}
"@
}

# .NET needs absolute paths; its working directory isn't PowerShell's current location.
$origPath    = (Resolve-Path -LiteralPath $Original).Path
$rebuiltPath = (Resolve-Path -LiteralPath $Rebuilt).Path

$origLen    = (Get-Item -LiteralPath $origPath).Length
$rebuiltLen = (Get-Item -LiteralPath $rebuiltPath).Length

"Original Track 1:      $origLen bytes ($($origLen / 2352) sectors)"
"Rebuilt image (total): $rebuiltLen bytes ($($rebuiltLen / 2352) sectors)"
"Rebuilt Track 1 SHA-1: $([SectorDiff]::Sha1Prefix($rebuiltPath, $origLen))"
""
[SectorDiff]::Diff($origPath, $rebuiltPath, $MaxLines)