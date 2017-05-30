BEGIN {
	IGNORECASE = 1;
	enc = "<html> <head> <meta charset='UTF-8'/> </head> <body>"
	fmtHREF = "<p><a href=\"%s.html\"> %s </a></p>\n";
	fmtIMG = "<li><center><img src=\"http://npmp.epl.di.uminho.pt/images/%s\"/> </center></li>\n"
	FS = "[<>\"]";
	end = "</body></html>";
	print enc > "index.html";
}


/<foto / {
	image = $3;
}

/<quem>/ && (length($3) < 200) {
	$3 = removeSpaces($3);
	album[$3][image] = 0;
}

/<onde>/ && !(($3 = removeSpaces($3)) in locals) {
	locals[$3] = 0;
}

END {
	for (i in album) {
		aux = removeInvalidChars(i);

		printf(fmtHREF, aux, i) > "index.html";

		print enc > aux".html";

		for (j in album[i]) {
			printf(fmtIMG, j) > aux".html";
		}

		print end > aux".html";
	}

	print "<p></p>\n<b>Locais:</b>\n" > "index.html";
	
	for (x in locals) {
		printf("<li>%s</li>\n", x) > "index.html";
	}

	print end > "index.html";
}

function removeSpaces(str) {
	sub("^ +", "", str);
	sub(" +$", "", str);

	return str;
}


function removeInvalidChars(str) {
	sub("[:\\t]", "", str);
	return str;
}
