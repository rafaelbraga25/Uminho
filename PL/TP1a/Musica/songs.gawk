BEGIN {
	FS = " *[:;,] *"
}

/title: / {
	song = $2;
	sub("\\(\\?\\)", "", song);
	sub("^[ *=]+", "", song);
}

/author:/ {
	for (i = 2; i <= NF; i++) {
		sub("[ ?()\\t]+$", "", $i);

		if ($i != "") {
			authors[$i][song] = song;
		}
		else {
			authors["Autor desconhecido"][song] = song;
		}

	}
}

END {
	for (a in authors) {
		printf("%s: ", a);

		flag = 0;		

		for (j in authors[a]) {
			if (flag == 0) {
				printf("%s", j);
			}
			else {
				printf(", %s", j);
			} 

			flag++;
		}

		printf("\n");
	}
}
