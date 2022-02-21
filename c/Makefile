wordbord:
	$(CC) $(CFLAGS) -o wordbord-solver $(LDLIBS) wordbord-solver.c analyze.c

# The below is the same as the makefile in the directory ~/code, it's only here for easier usage

rezip:
	@echo Rezipping...
	@if [ ! -d "$(HOME)/shares/Shared" ]; then make remount; fi
	@rm -rf files.zip
	@zip -r9 files * > /dev/null
	@mv -f files.zip ~/shares/Shared/
	@echo Rezipping done!

remount:
	@echo We need sudo to remount!
	@sudo /usr/bin/vmhgfs-fuse .host:/ ~/shares -o subtype=vmhgfs-fuse,allow_other 
