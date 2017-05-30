BEGIN {
	IGNORECASE = 1;
	FS = "[>-]";
}
/<data_entrada>[0-9]/ {
	auxDay = 0 + $2;
	auxMonth = 0 + $3;
	count[auxMonth][auxDay]++;
}
END {
	for (i = 1; i <= 12; i++) {
		if (i in count) {
			print "Mês: " i;

			for (j = 1; j <= 31; j++) {
				if (j in count[i]) {
					print "\tDia: " j " - " count[i][j] " entradas.";
				}
			} 
		}
	}
}
