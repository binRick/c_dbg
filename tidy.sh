uncrustify -c ./etc/uncrustify.cfg --replace tests/*.c include/*.c include/*.h src/*.c
shfmt -w *.sh
find . -name "*.unc-backup*" -type f | xargs -I % unlink %
js-beautify -r clib.json
