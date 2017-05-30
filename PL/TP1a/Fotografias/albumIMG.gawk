BEGIN {
	IGNORECASE = 1;
	fmtLI = "<li><b>%s</b></li>\n";
	fmtI = "<center><img src=\"http://npmp.epl.di.uminho.pt/images/%s\"/> </center>\n"
	FS = "[<>\"]";
	end = "</body></html>";
	print "<html><head><meta charset='UTF-8'/></head><body>" > "index.html";
}

/<foto / {
	image = $3;
}

/<quem>/ {
	$3 = removeSpaces($3);

	printf(fmtLI, $3) > "index.html";
	printf(fmtI, image) > "index.html";
}

/<onde>/ && !(($3 = removeSpaces($3)) in locals) {
	locals[$3] = 0;
}

END {
	print "<p></p>\n<b>Locais:</b>\n" > "index.html";
	
	for (i in locals) {
		printf("<li>%s</li>\n", i) > "index.html";
	}

	print end > "index.html";
}

function removeSpaces(str) {
	sub("^ +", "", str);
	sub(" +$", "", str);

	return str;
}
