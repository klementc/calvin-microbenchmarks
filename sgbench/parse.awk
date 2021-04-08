#!/usr/bin/awk -f

BEGIN {
}

/output service 1/{
	gsub(/]/, "")
	gsub(/\[/, "")
	print($2","$8","$10","$12","$14","$16","$18)
}

END {
}
