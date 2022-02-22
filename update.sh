commit () {
	# Request a commit message and give it to git
	set -o noclobber
	echo -n "Please enter a commit message: "
	read MESSAGE
	[[ ${#MESSAGE} -gt 72 ]] && { echo Message too long! Sorry; unset MESSAGE; exit 1; }
	echo $MESSAGE > .message.tmp
	git commit -F .message.tmp
	unset MESSAGE
	rm .message.tmp
	set +o noclobber
}

./rezip.sh
git add .
commit
git push -u origin master
echo Updating done!

