BEGIN {
	IGNORECASE = 1;
	FS = "[><]";
}
/<saida>/ && !($3 in list) {
	list[$3] = $3;
}
END {
	print "Lista de saídas:" 

	for (e in list) {
		print "\t" e;
	}
}
