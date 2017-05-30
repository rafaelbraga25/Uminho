BEGIN {
	IGNORECASE = 1;
	FS = "[><]";
}
/<importancia>/ {
	sub(",", ".", $3);
	imp = $3;
}
/<valor_desconto>/ {
	sub(",", ".", $3);
	desc = $3;
	total += imp - desc;
}
/<tipo>parque/ {
	totalP += imp - desc;
}
END {
	print "Total gasto: " total;
	print "Total gasto em parques: " totalP;
}
