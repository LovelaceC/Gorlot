all:
	@echo "Building Gorlot"
	@cd lib && make --no-print-directory -j`nproc`
	@echo "Building Editor"
	@cd editor && make --no-print-directory -j`nproc`

clean:
	@echo "Cleaning Library"
	@cd lib && make --no-print-directory clean
	@echo "Cleaning Editor"
	@cd editor && make --no-print-directory clean

run:
	@cd editor && make --no-print-directory run
