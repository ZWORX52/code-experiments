remount () {
	echo Requesting sudo so we can remount...
	sudo /usr/bin/vmhgfs-fuse .host:/ ~/shares -o subtype=vmhgfs-fuse,allow_other 
}

echo Rezipping...
if [ ! -d "/home/zworx52/shares/Shared" ]; then remount; fi
rm -rf files.zip
zip -r9 files * > /dev/null
mv -f files.zip ~/shares/Shared/

