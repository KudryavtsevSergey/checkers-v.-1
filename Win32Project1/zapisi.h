extern int movChess;

class clChess {
	public:
	int x, y, xG, yG, xG1, yG1;
	BOOL downing = FALSE;
	struct myChessStruct {
		BOOL chess, queen, shine, necesStrike;
		int color;
	};
	myChessStruct nShashka;
	BOOL isCheckStrike (myChessStruct raspChess[8][8]);
	BOOL isSelect (myChessStruct raspChess[8][8]);
	BOOL isSelectOne (myChessStruct raspChess[8][8]);
	BOOL isStrikeQueen (myChessStruct raspChess[8][8]);
	BOOL isDoubleStrikeQueen (myChessStruct raspChess[8][8]);
	BOOL isStrikeChess (myChessStruct raspChess[8][8]);
	BOOL isDoubleStrikeChess (myChessStruct raspChess[8][8]);
};

BOOL clChess::isCheckStrike (myChessStruct raspChess[8][8]) {
	BOOL vihodn = FALSE;
	for (signed int i = 0; i < 8; i++) {
		for (signed int j = 0; j < 8; j++) {
			if (i < 8 && j < 8 && ((i % 2) ^ (j % 2))) {
				raspChess[i][j].necesStrike = FALSE;
			}
		}
	}
	for (signed int i = 0; i < 8; i++) {
		for (signed int j = 0; j < 8; j++) {
			if (i < 8 && j < 8 && ((i % 2) ^ (j % 2))) {
				if (raspChess[i][j].color == movChess) {
					if (raspChess[i][j].chess) {
						if (!raspChess[i][j].queen) {
							if ((((i - 2 >= 0) && (j - 2 >= 0)) ? (raspChess[i - 1][j - 1].chess && (raspChess[i - 1][j - 1].color ^ raspChess[i][j].color) && (!raspChess[i - 2][j - 2].chess)) : false) ||
								(((i - 2 >= 0) && (j + 2 < 8)) ? (raspChess[i - 1][j + 1].chess && (raspChess[i - 1][j + 1].color ^ raspChess[i][j].color) && (!raspChess[i - 2][j + 2].chess)) : false) ||
								(((i + 2 < 8) && (j - 2 >= 0)) ? (raspChess[i + 1][j - 1].chess && (raspChess[i + 1][j - 1].color ^ raspChess[i][j].color) && (!raspChess[i + 2][j - 2].chess)) : false) ||
								(((i + 2 < 8) && (j + 2 < 8)) ? (raspChess[i + 1][j + 1].chess && (raspChess[i + 1][j + 1].color ^ raspChess[i][j].color) && (!raspChess[i + 2][j + 2].chess)) : false)) {
								raspChess[i][j].necesStrike = TRUE;
								vihodn = TRUE;
							}
						}
						else if (raspChess[i][j].queen) {
							for (signed int t = 1; t < 8; t++) {
								if ((raspChess[i - t][j - t].chess) && (raspChess[i - t][j - t].color == raspChess[i][j].color)) {
									break;
								}
								else if (((i - t - 1 >= 0) && (j - t - 1 >= 0)) ? (raspChess[i - t][j - t].chess && (raspChess[i - t][j - t].color ^ raspChess[i][j].color) && (raspChess[i - t - 1][j - t - 1].chess)) : true) {
									break;
								}
								else if (((i - t - 1 >= 0) && (j - t - 1 >= 0)) ? (raspChess[i - t][j - t].chess && (raspChess[i - t][j - t].color ^ raspChess[i][j].color) && (!raspChess[i - t - 1][j - t - 1].chess)) : false) {
									raspChess[i][j].necesStrike = TRUE;
									vihodn = TRUE;
									break;
								}
							}
							for (signed int t = 1; t < 8; t++) {
								if ((raspChess[i + t][j - t].chess) && (raspChess[i + t][j - t].color == raspChess[i][j].color)) {
									break;
								}
								else if (((i + t + 1 < 8) && (j - t - 1 >= 0)) ? (raspChess[i + t][j - t].chess && (raspChess[i + t][j - t].color ^ raspChess[i][j].color) && (raspChess[i + t + 1][j - t - 1].chess)) : true) {
									break;
								}
								else if (((i + t + 1 < 8) && (j - t - 1 >= 0)) ? (raspChess[i + t][j - t].chess && (raspChess[i + t][j - t].color ^ raspChess[i][j].color) && (!raspChess[i + t + 1][j - t - 1].chess)) : false) {
									raspChess[i][j].necesStrike = TRUE;
									vihodn = TRUE;
									break;
								}
							}
							for (signed int t = 1; t < 8; t++) {
								if ((raspChess[i - t][j + t].chess) && (raspChess[i - t][j + t].color == raspChess[i][j].color)) {
									break;
								}
								else if (((i - t - 1 >= 0) && (j + t + 1 < 8)) ? (raspChess[i - t][j + t].chess && (raspChess[i - t][j + t].color ^ raspChess[i][j].color) && (raspChess[i - t - 1][j + t + 1].chess)) : true) {
									break;
								}
								else if (((i - t - 1 >= 0) && (j + t + 1 < 8)) ? (raspChess[i - t][j + t].chess && (raspChess[i - t][j + t].color ^ raspChess[i][j].color) && (!raspChess[i - t - 1][j + t + 1].chess)) : false) {
									raspChess[i][j].necesStrike = TRUE;
									vihodn = TRUE;
									break;
								}
							}
							for (signed int t = 1; t < 8; t++) {
								if ((raspChess[i + t][j + t].chess) && (raspChess[i + t][j + t].color == raspChess[i][j].color)) {
									break;
								}
								else if (((i + t + 1 < 8) && (j + t + 1 < 8)) ? (raspChess[i + t][j + t].chess && (raspChess[i + t][j + t].color ^ raspChess[i][j].color) && (raspChess[i + t + 1][j + t + 1].chess)) : true) {
									break;
								}
								else if (((i + t + 1 < 8) && (j + t + 1 < 8)) ? (raspChess[i + t][j + t].chess && (raspChess[i + t][j + t].color ^ raspChess[i][j].color) && (!raspChess[i + t + 1][j + t + 1].chess)) : false) {
									raspChess[i][j].necesStrike = TRUE;
									vihodn = TRUE;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
	return vihodn;
}

BOOL clChess::isSelect (myChessStruct raspChess[8][8]) {
	if (x < 8 && y < 8 && ((y % 2) ^ (x % 2))) {
		if (raspChess[x][y].chess) {
			if (raspChess[x][y].color == movChess) {
				if (raspChess[x][y].queen) {
					if (((((x - 1 >= 0) && (y - 1 >= 0)) ? !(raspChess[x - 1][y - 1].chess) : false) ||
						(((x - 1 >= 0) && (y + 1 < 8)) ? !(raspChess[x - 1][y + 1].chess) : false) ||
						(((x + 1 < 8) && (y - 1 >= 0)) ? !(raspChess[x + 1][y - 1].chess) : false) ||
						(((x + 1 < 8) && (y + 1 < 8)) ? !(raspChess[x + 1][y + 1].chess) : false)) ||
						((((x - 2 >= 0) && (y - 2 >= 0)) ? (raspChess[x - 1][y - 1].chess && (raspChess[x - 1][y - 1].color ^ movChess) && (!raspChess[x - 2][y - 2].chess)) : false) ||
						(((x - 2 >= 0) && (y + 2 < 8)) ? (raspChess[x - 1][y + 1].chess && (raspChess[x - 1][y + 1].color ^ movChess) && (!raspChess[x - 2][y + 2].chess)) : false) ||
						(((x + 2 < 8) && (y - 2 >= 0)) ? (raspChess[x + 1][y - 1].chess && (raspChess[x + 1][y - 1].color ^ movChess) && (!raspChess[x + 2][y - 2].chess)) : false) ||
						(((x + 2 < 8) && (y + 2 < 8)) ? (raspChess[x + 1][y + 1].chess && (raspChess[x + 1][y + 1].color ^ movChess) && (!raspChess[x + 2][y + 2].chess)) : false))) {
						return TRUE;
					}
				}
				else {
					if (raspChess[x][y].color == WH) {
						if (((((x - 1 >= 0) && (y - 1 >= 0)) ? !(raspChess[x - 1][y - 1].chess) : false) ||
							(((x - 1 >= 0) && (y + 1 < 8)) ? !(raspChess[x - 1][y + 1].chess) : false)) ||
							((((x - 2 >= 0) && (y - 2 >= 0)) ? (raspChess[x - 1][y - 1].chess && (raspChess[x - 1][y - 1].color ^ movChess) && (!raspChess[x - 2][y - 2].chess)) : false) ||
							(((x - 2 >= 0) && (y + 2 < 8)) ? (raspChess[x - 1][y + 1].chess && (raspChess[x - 1][y + 1].color ^ movChess) && (!raspChess[x - 2][y + 2].chess)) : false) ||
							(((x + 2 < 8) && (y - 2 >= 0)) ? (raspChess[x + 1][y - 1].chess && (raspChess[x + 1][y - 1].color ^ movChess) && (!raspChess[x + 2][y - 2].chess)) : false) ||
							(((x + 2 < 8) && (y + 2 < 8)) ? (raspChess[x + 1][y + 1].chess && (raspChess[x + 1][y + 1].color ^ movChess) && (!raspChess[x + 2][y + 2].chess)) : false))) {
							return TRUE;
						}
					}
					else if (raspChess[x][y].color == BL) {
						if (((((x + 1 < 8) && (y - 1 >= 0)) ? !(raspChess[x + 1][y - 1].chess) : false) ||
							(((x + 1 < 8) && (y + 1 < 8)) ? !(raspChess[x + 1][y + 1].chess) : false)) ||
							((((x - 2 >= 0) && (y - 2 >= 0)) ? (raspChess[x - 1][y - 1].chess && (raspChess[x - 1][y - 1].color ^ movChess) && (!raspChess[x - 2][y - 2].chess)) : false) ||
							(((x - 2 >= 0) && (y + 2 < 8)) ? (raspChess[x - 1][y + 1].chess && (raspChess[x - 1][y + 1].color ^ movChess) && (!raspChess[x - 2][y + 2].chess)) : false) ||
							(((x + 2 < 8) && (y - 2 >= 0)) ? (raspChess[x + 1][y - 1].chess && (raspChess[x + 1][y - 1].color ^ movChess) && (!raspChess[x + 2][y - 2].chess)) : false) ||
							(((x + 2 < 8) && (y + 2 < 8)) ? (raspChess[x + 1][y + 1].chess && (raspChess[x + 1][y + 1].color ^ movChess) && (!raspChess[x + 2][y + 2].chess)) : false))) {
							return TRUE;
						}
					}
				}
			}
		}
	}
	return FALSE;
}

BOOL clChess::isSelectOne (myChessStruct raspChess[8][8]) {
	if (raspChess[x][y].color == movChess) {
		if (!downing) {
			if (raspChess[x][y].queen) {
				if (((((x - 1 >= 0) && (y - 1 >= 0)) ? !(raspChess[x - 1][y - 1].chess) : false) ||
					(((x - 1 >= 0) && (y + 1 < 8)) ? !(raspChess[x - 1][y + 1].chess) : false) ||
					(((x + 1 < 8) && (y - 1 >= 0)) ? !(raspChess[x + 1][y - 1].chess) : false) ||
					(((x + 1 < 8) && (y + 1 < 8)) ? !(raspChess[x + 1][y + 1].chess) : false)) ||
					((((x - 2 >= 0) && (y - 2 >= 0)) ? (raspChess[x - 1][y - 1].chess && (raspChess[x - 1][y - 1].color ^ movChess) && (!raspChess[x - 2][y - 2].chess)) : false) ||
					(((x - 2 >= 0) && (y + 2 < 8)) ? (raspChess[x - 1][y + 1].chess && (raspChess[x - 1][y + 1].color ^ movChess) && (!raspChess[x - 2][y + 2].chess)) : false) ||
					(((x + 2 < 8) && (y - 2 >= 0)) ? (raspChess[x + 1][y - 1].chess && (raspChess[x + 1][y - 1].color ^ movChess) && (!raspChess[x + 2][y - 2].chess)) : false) ||
					(((x + 2 < 8) && (y + 2 < 8)) ? (raspChess[x + 1][y + 1].chess && (raspChess[x + 1][y + 1].color ^ movChess) && (!raspChess[x + 2][y + 2].chess)) : false))) {
					return TRUE;
				}
			}
			else {
				if (raspChess[x][y].color == WH) {
					if (((((x - 1 >= 0) && (y - 1 >= 0)) ? !(raspChess[x - 1][y - 1].chess) : false) ||
						(((x - 1 >= 0) && (y + 1 < 8)) ? !(raspChess[x - 1][y + 1].chess) : false)) ||
						((((x - 2 >= 0) && (y - 2 >= 0)) ? (raspChess[x - 1][y - 1].chess && (raspChess[x - 1][y - 1].color ^ movChess) && (!raspChess[x - 2][y - 2].chess)) : false) ||
						(((x - 2 >= 0) && (y + 2 < 8)) ? (raspChess[x - 1][y + 1].chess && (raspChess[x - 1][y + 1].color ^ movChess) && (!raspChess[x - 2][y + 2].chess)) : false) ||
						(((x + 2 < 8) && (y - 2 >= 0)) ? (raspChess[x + 1][y - 1].chess && (raspChess[x + 1][y - 1].color ^ movChess) && (!raspChess[x + 2][y - 2].chess)) : false) ||
						(((x + 2 < 8) && (y + 2 < 8)) ? (raspChess[x + 1][y + 1].chess && (raspChess[x + 1][y + 1].color ^ movChess) && (!raspChess[x + 2][y + 2].chess)) : false))) {
						return TRUE;
					}
				}
				else if (raspChess[x][y].color == BL) {
					if (((((x + 1 < 8) && (y - 1 >= 0)) ? !(raspChess[x + 1][y - 1].chess) : false) ||
						(((x + 1 < 8) && (y + 1 < 8)) ? !(raspChess[x + 1][y + 1].chess) : false)) ||
						((((x - 2 >= 0) && (y - 2 >= 0)) ? (raspChess[x - 1][y - 1].chess && (raspChess[x - 1][y - 1].color ^ movChess) && (!raspChess[x - 2][y - 2].chess)) : false) ||
						(((x - 2 >= 0) && (y + 2 < 8)) ? (raspChess[x - 1][y + 1].chess && (raspChess[x - 1][y + 1].color ^ movChess) && (!raspChess[x - 2][y + 2].chess)) : false) ||
						(((x + 2 < 8) && (y - 2 >= 0)) ? (raspChess[x + 1][y - 1].chess && (raspChess[x + 1][y - 1].color ^ movChess) && (!raspChess[x + 2][y - 2].chess)) : false) ||
						(((x + 2 < 8) && (y + 2 < 8)) ? (raspChess[x + 1][y + 1].chess && (raspChess[x + 1][y + 1].color ^ movChess) && (!raspChess[x + 2][y + 2].chess)) : false))) {
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

BOOL clChess::isStrikeQueen (myChessStruct raspChess[8][8]) {
	if ((x - y == xG - yG) || (x + y == xG + yG)) {
		xG1 = (x - xG) / abs (x - xG);
		yG1 = (y - yG) / abs (y - yG);
		int podschet = 0;
		int k = abs (x - xG);
		for (signed int i = 1; i < k; i++) {
			if ((raspChess[xG + i*xG1][yG + i*yG1].chess) && (raspChess[xG + i*xG1][yG + i*yG1].color == movChess)) {
				return FALSE;
			}
			else if ((((xG + (i + 1)*xG1 >= 0) && (yG + (i + 1)*yG1 >= 0)) && ((xG + (i + 1)*xG1 < 8) && (yG + (i + 1)*yG1 < 8))) ?
					 (raspChess[xG + i*xG1][yG + i*yG1].chess && (raspChess[xG + i*xG1][yG + i*yG1].color ^ movChess) && (raspChess[xG + (i + 1)*xG1][yG + (i + 1)*yG1].chess)) : true) {
				return FALSE;
			}
			else if ((((xG + (i + 1)*xG1 >= 0) && (yG + (i + 1)*yG1 >= 0)) && ((xG + (i + 1)*xG1 < 8) && (yG + (i + 1)*yG1 < 8))) ?
					 (raspChess[xG + i*xG1][yG + i*yG1].chess && (raspChess[xG + i*xG1][yG + i*yG1].color ^ movChess) && (!raspChess[xG + (i + 1)*xG1][yG + (i + 1)*yG1].chess)) : false) {
				podschet++;
				downing = TRUE;
			}
			if (podschet > 1) {
				downing = FALSE;
				return FALSE;
			}
		}
		raspChess[x][y] = nShashka;
		return TRUE;
	}
	return FALSE;
}

BOOL clChess::isDoubleStrikeQueen (myChessStruct raspChess[8][8]) {
	if (downing) {
		for (signed int i = 1; i < 8; i++) {
			if ((x - i == xG) && (y - i == yG)) {
				break;
			}
			else if ((raspChess[x - i][y - i].chess) && (raspChess[x - i][y - i].color == movChess)) {
				break;
			}
			else if (((x - i - 1 >= 0) && (y - i - 1 >= 0)) ? (raspChess[x - i][y - i].chess && (raspChess[x - i][y - i].color ^ movChess) && (raspChess[x - i - 1][y - i - 1].chess)) : true) {
				break;
			}
			else if (((x - i - 1 >= 0) && (y - i - 1 >= 0)) ? (raspChess[x - i][y - i].chess && (raspChess[x - i][y - i].color ^ movChess) && (!raspChess[x - i - 1][y - i - 1].chess)) : false) {
				return FALSE;
			}
		}
		for (signed int i = 1; i < 8; i++) {
			if ((x + i == xG) && (y - i == yG)) {
				break;
			}
			else if ((raspChess[x + i][y - i].chess) && (raspChess[x + i][y - i].color == movChess)) {
				break;
			}
			else if (((x + i + 1 < 8) && (y - i - 1 >= 0)) ? (raspChess[x + i][y - i].chess && (raspChess[x + i][y - i].color ^ movChess) && (raspChess[x + i + 1][y - i - 1].chess)) : true) {
				break;
			}
			else if (((x + i + 1 < 8) && (y - i - 1 >= 0)) ? (raspChess[x + i][y - i].chess && (raspChess[x + i][y - i].color ^ movChess) && (!raspChess[x + i + 1][y - i - 1].chess)) : false) {
				return FALSE;
			}
		}
		for (signed int i = 1; i < 8; i++) {
			if ((x - i == xG) && (y + i == yG)) {
				break;
			}
			else if ((raspChess[x - i][y + i].chess) && (raspChess[x - i][y + i].color == movChess)) {
				break;
			}
			else if (((x - i - 1 >= 0) && (y + i + 1 < 8)) ? (raspChess[x - i][y + i].chess && (raspChess[x - i][y + i].color ^ movChess) && (raspChess[x - i - 1][y + i + 1].chess)) : true) {
				break;
			}
			else if (((x - i - 1 >= 0) && (y + i + 1 < 8)) ? (raspChess[x - i][y + i].chess && (raspChess[x - i][y + i].color ^ movChess) && (!raspChess[x - i - 1][y + i + 1].chess)) : false) {
				return FALSE;
			}
		}
		for (signed int i = 1; i < 8; i++) {
			if ((x + i == xG) && (y + i == yG)) {
				break;
			}
			else if ((raspChess[x + i][y + i].chess) && (raspChess[x + i][y + i].color == movChess)) {
				break;
			}
			else if (((x + i + 1 < 8) && (y + i + 1 < 8)) ? (raspChess[x + i][y + i].chess && (raspChess[x + i][y + i].color ^ movChess) && (raspChess[x + i + 1][y + i + 1].chess)) : true) {
				break;
			}
			else if (((x + i + 1 < 8) && (y + i + 1 < 8)) ? (raspChess[x + i][y + i].chess && (raspChess[x + i][y + i].color ^ movChess) && (!raspChess[x + i + 1][y + i + 1].chess)) : false) {
				return FALSE;
			}
		}
	}
	return TRUE;
}

BOOL clChess::isStrikeChess (myChessStruct raspChess[8][8]) {
	if (raspChess[xG][yG].color == WH) {
		if (((((x + 1 == xG) && (y + 1 == yG)) ? !(raspChess[x][y].chess) : false) ||
			(((x + 1 == xG) && (y - 1 == yG)) ? !(raspChess[x][y].chess) : false)) ||
			((((x + 2 == xG) && (y + 2 == yG)) ? (raspChess[x + 1][y + 1].chess && (raspChess[x + 1][y + 1].color ^ movChess) && (!raspChess[x][y].chess)) : false) ||
			(((x + 2 == xG) && (y - 2 == yG)) ? (raspChess[x + 1][y - 1].chess && (raspChess[x + 1][y - 1].color ^ movChess) && (!raspChess[x][y].chess)) : false) ||
			(((x - 2 == xG) && (y + 2 == yG)) ? (raspChess[x - 1][y + 1].chess && (raspChess[x - 1][y + 1].color ^ movChess) && (!raspChess[x][y].chess)) : false) ||
			(((x - 2 == xG) && (y - 2 == yG)) ? (raspChess[x - 1][y - 1].chess && (raspChess[x - 1][y - 1].color ^ movChess) && (!raspChess[x][y].chess)) : false))) {
			raspChess[xG][yG].chess = FALSE;
			raspChess[xG][yG].shine = FALSE;
			raspChess[xG][yG].queen = FALSE;
			raspChess[xG][yG].color = 2;

			raspChess[x][y] = nShashka;
			if (x == 0) {
				raspChess[x][y].queen = TRUE;
			}
			return TRUE;
		}
	}
	else if (raspChess[xG][yG].color == BL) {
		if (((((x - 1 == xG) && (y + 1 == yG)) ? !(raspChess[x][y].chess) : false) ||
			(((x - 1 == xG) && (y - 1 == yG)) ? !(raspChess[x][y].chess) : false)) ||
			((((x + 2 == xG) && (y + 2 == yG)) ? (raspChess[x + 1][y + 1].chess && (raspChess[x + 1][y + 1].color ^ movChess) && (!raspChess[x][y].chess)) : false) ||
			(((x + 2 == xG) && (y - 2 == yG)) ? (raspChess[x + 1][y - 1].chess && (raspChess[x + 1][y - 1].color ^ movChess) && (!raspChess[x][y].chess)) : false) ||
			(((x - 2 == xG) && (y + 2 == yG)) ? (raspChess[x - 1][y + 1].chess && (raspChess[x - 1][y + 1].color ^ movChess) && (!raspChess[x][y].chess)) : false) ||
			(((x - 2 == xG) && (y - 2 == yG)) ? (raspChess[x - 1][y - 1].chess && (raspChess[x - 1][y - 1].color ^ movChess) && (!raspChess[x][y].chess)) : false))) {
			raspChess[xG][yG].chess = FALSE;
			raspChess[xG][yG].shine = FALSE;
			raspChess[xG][yG].queen = FALSE;
			raspChess[xG][yG].color = 2;

			raspChess[x][y] = nShashka;
			if (x == 7) {
				raspChess[x][y].queen = TRUE;
			}
			return TRUE;
		}
	}
	return FALSE;
}

BOOL clChess::isDoubleStrikeChess (myChessStruct raspChess[8][8]) {
	if (((((x - 2 >= 0) && (y - 2 >= 0)) ? (raspChess[x - 1][y - 1].chess && (raspChess[x - 1][y - 1].color ^ movChess) && (!raspChess[x - 2][y - 2].chess)) : false) ||
		(((x - 2 >= 0) && (y + 2 < 8)) ? (raspChess[x - 1][y + 1].chess && (raspChess[x - 1][y + 1].color ^ movChess) && (!raspChess[x - 2][y + 2].chess)) : false) ||
		(((x + 2 < 8) && (y - 2 >= 0)) ? (raspChess[x + 1][y - 1].chess && (raspChess[x + 1][y - 1].color ^ movChess) && (!raspChess[x + 2][y - 2].chess)) : false) ||
		(((x + 2 < 8) && (y + 2 < 8)) ? (raspChess[x + 1][y + 1].chess && (raspChess[x + 1][y + 1].color ^ movChess) && (!raspChess[x + 2][y + 2].chess)) : false)) &&
		((x - 2 * xG1 == xG) && (y - 2 * yG1 == yG))) {
		return FALSE;
	}
	return TRUE;
}