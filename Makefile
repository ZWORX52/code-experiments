rezip:
	@echo Rezipping...
	@if [ ! -d "/home/zworx52/shares/Shared" ]; then make remount; fi
	@rm -rf files.zip
	@zip -r9 files * > /dev/null
	@mv -f files.zip ~/shares/Shared/
	@echo Rezipping done!

remount:
	@echo We need sudo to remount!
	@sudo /usr/bin/vmhgfs-fuse .host:/ ~/shares -o subtype=vmhgfs-fuse,allow_other 
