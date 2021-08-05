krml_link = krml -warn-error +9 -drop WasmSupport -tmpdir ./out -fsopt --cache_dir -fsopt ./out -fsopt --cache_checked_modules -o ./out/validatePacketData -no-prefix ValidatePacketData validatePacketData.fst

exec = ./out/validatePacketData

all: test
	$(krml_link) main.c && $(exec)
test:
	$(krml_link) -verify test.c && $(exec) || (echo "validatePacketData func is not implemented" && exit 1)
