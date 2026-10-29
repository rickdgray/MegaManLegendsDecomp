// Export named functions and globals to splat's symbol_addrs.txt format.
// Skips Ghidra default names, labels inside functions, namespaced (switch) labels,
// non-primary labels, names that aren't valid assembler identifiers, duplicates,
// and the PSX loader's artificial GTEMAC block (not real memory).
// Addresses below 0x80000000 (scratchpad, hardware registers) are tagged absolute:True.
// Names defined in symbol_addrs_manual.txt (same folder as the output) are skipped,
// so hand-maintained overrides always win.
//@category Export

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.mem.MemoryBlock;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;
import ghidra.program.model.symbol.SymbolType;

import java.io.File;
import java.nio.file.Files;
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;

public class ExportSplatSymbols extends GhidraScript {

    private static final String VALID_NAME = "[A-Za-z_][A-Za-z0-9_]*";

    @Override
    public void run() throws Exception {
        File out = askFile("Save symbol_addrs.txt", "Save");
        Listing listing = currentProgram.getListing();

        // Names maintained by hand take priority over Ghidra's.
        Set<String> manual = new HashSet<>();
        File manualFile = new File(out.getParentFile(), "symbol_addrs_manual.txt");
        if (manualFile.exists()) {
            for (String line : Files.readAllLines(manualFile.toPath())) {
                String t = line.trim();
                if (t.isEmpty() || t.startsWith("//") || !t.contains("=")) continue;
                manual.add(t.substring(0, t.indexOf('=')).trim());
            }
            printf("Read %d manual symbols from %s%n", manual.size(), manualFile);
        }
        int skippedManual = 0;

        TreeMap<Long, String> lines = new TreeMap<>();
        Set<String> seen = new HashSet<>();
        int funcs = 0, globals = 0, skippedDup = 0, skippedName = 0;

        SymbolIterator it = currentProgram.getSymbolTable().getAllSymbols(true);
        while (it.hasNext() && !monitor.isCancelled()) {
            Symbol s = it.next();

            if (s.getSource() == SourceType.DEFAULT) continue;   // FUN_, DAT_, LAB_, ...
            if (!s.isPrimary()) continue;
            if (!s.getParentNamespace().isGlobal()) continue;    // switchD_* case labels
            Address a = s.getAddress();
            if (!a.isMemoryAddress()) continue;

            MemoryBlock block = currentProgram.getMemory().getBlock(a);
            if (block != null && block.getName().equals("GTEMAC")) continue;   // fake GTE macro addresses

            String name = s.getName();
            boolean isFunc = s.getSymbolType() == SymbolType.FUNCTION;
            boolean isLabel = s.getSymbolType() == SymbolType.LABEL;
            if (!isFunc && !isLabel) continue;

            // Labels inside function bodies are jump targets, not globals.
            if (isLabel && listing.getFunctionContaining(a) != null) continue;

            if (!name.matches(VALID_NAME)) {
                printf("Skipped (not a valid assembler name): %s @ %s%n", name, a);
                skippedName++;
                continue;
            }
            if (manual.contains(name)) {
                skippedManual++;
                continue;
            }
            if (!seen.add(name)) {
                printf("Skipped duplicate name: %s @ %s%n", name, a);
                skippedDup++;
                continue;
            }

            long addr = a.getOffset();
            String attrs;
            if (isFunc) {
                attrs = " // type:func";
                funcs++;
            } else {
                Data d = listing.getDataAt(a);
                attrs = (d != null && d.isDefined() && d.getLength() > 0)
                        ? String.format(" // size:0x%X", d.getLength())
                        : "";
                globals++;
            }
            if (addr < 0x80000000L) {
                // Scratchpad and hardware registers: fixed addresses outside any splat segment.
                attrs = (attrs.isEmpty() ? " //" : attrs) + " absolute:True";
            }
            lines.put(addr, String.format("%s = 0x%08X;%s", name, addr, attrs));
        }

        try (PrintWriter w = new PrintWriter(out, "UTF-8")) {
            for (Map.Entry<Long, String> e : lines.entrySet()) {
                w.println(e.getValue());
            }
        }

        printf("Wrote %d functions and %d globals to %s%n", funcs, globals, out);
        printf("Skipped %d invalid names, %d duplicates, %d manual overrides%n",
               skippedName, skippedDup, skippedManual);
    }
}