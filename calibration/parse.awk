#!/usr/bin/awk -f


/finished/{
	gsub(/]/, "")
	gsub(/\[/, "")
	print($8","$10","$12)
}

END {
}
