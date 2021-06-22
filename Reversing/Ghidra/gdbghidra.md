gdbghidra

gdbghidra

[github.com/Comescuris/gdbghidra](github.com/Comesecuris/gdbghidra)

# Setup
1. Edit ~/.gdbinit configuration file to include plugin
	`source <path_to>/gdb_ghidra_bridge_client.py`
2. Open GHIDRA and select File/Install Extensions
3. Press the green + button and select dist/ghidra_9.0.1_PUBLIC_*_GDBGHIDRA.zip
4. Start GHIDRA CodeBrowser
5. Open File/Configure and press the adapter icon on the left of Ghidra Core , may be in developmental
6. Filter for gdb and make sure GDBGhidraPluin is enabled


## Connection
1. Open GDBGhidraPlugin window and configure listener port using the cog button
2. Within gdb... connect gdb stub to gdbghidra's port
`ghidrabridge ip:port`