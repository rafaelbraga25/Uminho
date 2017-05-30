BEGIN {

	FS = " *[:;,] *"
}

/singer:/ {
	for (i = 2; i <= NF; i++) {
		sub("[ ?()]+$", "", $i);

		if (!($i in singers) && ($i != "")) {
			count++;
			singers[$i] = $i;
		}
	}
}

END {
	n = asort(singers);

	for (i = 1; i <= n; i++) {
		print singers[i];
	}

	print "Total: " count;
}
