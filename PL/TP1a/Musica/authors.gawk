BEGIN {
	FS = " *[:;,] *"
}

/author:/ {
	for (i = 2; i <= NF; i++) {
		sub("[ ?()\\t]+$", "", $i);

		if ($i != "") {
			songs[$i]++;
		}
		else {
			songs["Autor desconhecido"]++;
		}

	}
}

END {
	for (i in songs) {
		print i " - " songs[i];
	}
}

