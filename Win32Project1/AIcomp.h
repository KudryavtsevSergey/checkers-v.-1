class aiComp {
	public:
	struct myList {
		struct mySpHodov {
			clChess::myChessStruct raspChess[8][8];
			int ocenka;
			BOOL dophod;
			mySpHodov *next;
			myList *sledHod;
		};
		mySpHodov *first, *last;
	};
	clChess::myChessStruct hodComp[8][8];
	int maxSum;
	int podschetHodov;
	void Initial (myList *listSost);
	void Del (myList *listSost);
	myList* Addlist (myList **listSost, clChess::myChessStruct raspChess[8][8]);
	myList* podborHodov (myList *listSost, clChess::myChessStruct raspChess[8][8], int movCh, int vlojen);
	myList* podborOneHodov (myList *listSost, clChess::myChessStruct raspChess[8][8], int x, int y, int movCh, int vlojen);
	BOOL isCheckStrike (clChess::myChessStruct raspChess[8][8], int movCh);
	BOOL isCheckOneStrike (clChess::myChessStruct raspChess[8][8], int x, int y, int movCh);
	void isStrike (int *ocenka, clChess::myChessStruct raspChess[8][8], int x, int y, int xOn, int yOn);
	void isMove (int *ocenka, clChess::myChessStruct raspChess[8][8], int x, int y, int xOn, int yOn);
	void copy (clChess::myChessStruct oneMass[8][8], clChess::myChessStruct twoMass[8][8]);
	void poiskHoda (myList *listSost, clChess::myChessStruct raspChess[8][8], int podschet, BOOL prover);
};

void aiComp::Initial (myList *listSost) {
	(*listSost).first = new myList::mySpHodov;
	(*listSost).first = NULL;
	(*listSost).last = NULL;
}

void aiComp::Del (myList *listSost) {
	myList::mySpHodov *dopHod;
	if (listSost != NULL) {
		dopHod = (*listSost).first;
		while (dopHod != NULL) {
			Del ((*dopHod).sledHod);
			dopHod = (*dopHod).next;
		}
		delete dopHod;
	}
}

aiComp::myList* aiComp::Addlist (myList **listSost, clChess::myChessStruct raspChess[8][8]) {
	myList::mySpHodov* vrMove;
	if (*listSost == NULL) {
		*listSost = new myList;
		(*(*listSost)).first = NULL;
	}
	vrMove = new myList::mySpHodov;
	copy ((*vrMove).raspChess, raspChess);
	(*vrMove).sledHod = NULL;
	(*vrMove).ocenka = 0;
	(*vrMove).dophod = FALSE;
	(*vrMove).next = NULL;
	if ((*(*listSost)).first == NULL) {
		(*(*listSost)).first = vrMove;
	}
	else {
		(*(*(*listSost)).last).next = vrMove;
	}
	(*(*listSost)).last = vrMove;
	return *listSost;
}



aiComp::myList* aiComp::podborHodov (myList *listSost, clChess::myChessStruct raspChess[8][8], int movCh, int vlojen) {
	if (vlojen >= 0) {
		if (isCheckStrike (raspChess, movCh)) {
			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {
					if (x < 8 && y < 8 && ((x % 2) ^ (y % 2)) && raspChess[x][y].necesStrike) {
						if (!raspChess[x][y].queen) {
							if (raspChess[x][y].color == movCh) {
								if (((x - 2 >= 0) && (y - 2 >= 0)) ? (raspChess[x - 1][y - 1].chess && (raspChess[x - 1][y - 1].color ^ movCh) && (!raspChess[x - 2][y - 2].chess)) : false) {
									listSost = Addlist (&listSost, raspChess);
									isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x - 2, y - 2);
									if (isCheckOneStrike ((*(*listSost).last).raspChess, x - 2, y - 2, movCh)) {
										(*(*listSost).last).dophod = TRUE;
										(*(*listSost).last).sledHod = podborOneHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, x - 2, y - 2, movCh, vlojen - 1);
									}
									else {
										(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 1);
									}
								}
								if (((x - 2 >= 0) && (y + 2 < 8)) ? (raspChess[x - 1][y + 1].chess && (raspChess[x - 1][y + 1].color ^ movCh) && (!raspChess[x - 2][y + 2].chess)) : false) {
									listSost = Addlist (&listSost, raspChess);
									isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x - 2, y + 2);
									if (isCheckOneStrike ((*(*listSost).last).raspChess, x - 2, y + 2, movCh)) {
										(*(*listSost).last).dophod = TRUE;
										(*(*listSost).last).sledHod = podborOneHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, x - 2, y + 2, movCh, vlojen - 1);
									}
									else {
										(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 1);
									}
								}
								if (((x + 2 < 8) && (y - 2 >= 0)) ? (raspChess[x + 1][y - 1].chess && (raspChess[x + 1][y - 1].color ^ movCh) && (!raspChess[x + 2][y - 2].chess)) : false) {
									listSost = Addlist (&listSost, raspChess);
									isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x + 2, y - 2);
									if (isCheckOneStrike ((*(*listSost).last).raspChess, x + 2, y - 2, movCh)) {
										(*(*listSost).last).dophod = TRUE;
										(*(*listSost).last).sledHod = podborOneHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, x + 2, y - 2, movCh, vlojen - 1);
									}
									else {
										(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 1);
									}
								}
								if (((x + 2 < 8) && (y + 2 < 8)) ? (raspChess[x + 1][y + 1].chess && (raspChess[x + 1][y + 1].color ^ movCh) && (!raspChess[x + 2][y + 2].chess)) : false) {
									listSost = Addlist (&listSost, raspChess);
									isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x + 2, y + 2);
									if (isCheckOneStrike ((*(*listSost).last).raspChess, x + 2, y + 2, movCh)) {
										(*(*listSost).last).dophod = TRUE;
										(*(*listSost).last).sledHod = podborOneHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, x + 2, y + 2, movCh, vlojen - 1);
									}
									else {
										(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 1);
									}
								}
							}
						}
						else if (raspChess[x][y].queen) {
							if (raspChess[x][y].color == movCh) {
								for (signed int t = 1; t < 8; t++) {
									if (((x - t >= 0) && (y - t >= 0)) ? ((raspChess[x - t][y - t].chess) && (raspChess[x - t][y - t].color == movCh)) : true) {
										break;
									}
									else if (((x - t - 1 >= 0) && (y - t - 1 >= 0)) ? (raspChess[x - t][y - t].chess && (raspChess[x - t][y - t].color ^ movCh) && (raspChess[x - t - 1][y - t - 1].chess)) : true) {
										break;
									}
									else if (((x - t - 1 >= 0) && (y - t - 1 >= 0)) ? (raspChess[x - t][y - t].chess && (raspChess[x - t][y - t].color ^ movCh) && (!raspChess[x - t - 1][y - t - 1].chess)) : false) {
										for (signed int o = t; o < 8; o++) {
											if ((x - o - 1 >= 0) && (y - o - 1 >= 0)) {
												if (!raspChess[x - o - 1][y - o - 1].chess) {
													listSost = Addlist (&listSost, raspChess);
													isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x - o - 1, y - o - 1);
													if (isCheckOneStrike ((*(*listSost).last).raspChess, x - o - 1, y - o - 1, movCh)) {
														(*(*listSost).last).dophod = TRUE;
														(*(*listSost).last).sledHod = podborOneHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, x - o - 1, y - o - 1, movCh, vlojen - 2);
													}
													else {
														(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 2);
													}
												}
												else break;
											}
											else {
												break;
											}
										}
										break;
									}
								}
								for (signed int t = 1; t < 8; t++) {
									if (((x + t < 8) && (y - t >= 0)) ? ((raspChess[x + t][y - t].chess) && (raspChess[x + t][y - t].color == movCh)) : true) {
										break;
									}
									else if (((x + t + 1 < 8) && (y - t - 1 >= 0)) ? (raspChess[x + t][y - t].chess && (raspChess[x + t][y - t].color ^ movCh) && (raspChess[x + t + 1][y - t - 1].chess)) : true) {
										break;
									}
									else if (((x + t + 1 < 8) && (y - t - 1 >= 0)) ? (raspChess[x + t][y - t].chess && (raspChess[x + t][y - t].color ^ movCh) && (!raspChess[x + t + 1][y - t - 1].chess)) : false) {
										for (signed int o = t; o < 8; o++) {
											if ((x + o + 1 < 8) && (y - o - 1 >= 0)) {
												if (!raspChess[x + o + 1][y - o - 1].chess) {
													listSost = Addlist (&listSost, raspChess);
													isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x + o + 1, y - o - 1);
													if (isCheckOneStrike ((*(*listSost).last).raspChess, x + o + 1, y - o - 1, movCh)) {
														(*(*listSost).last).dophod = TRUE;
														(*(*listSost).last).sledHod = podborOneHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, x + o + 1, y - o - 1, movCh, vlojen - 2);
													}
													else {
														(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 2);
													}
												}
												else break;
											}
											else {
												break;
											}
										}
										break;
									}
								}
								for (signed int t = 1; t < 8; t++) {
									if (((x - t >= 0) && (y + t < 8)) ? ((raspChess[x - t][y + t].chess) && (raspChess[x - t][y + t].color == movCh)) : true) {
										break;
									}
									else if (((x - t - 1 >= 0) && (y + t + 1 < 8)) ? (raspChess[x - t][y + t].chess && (raspChess[x - t][y + t].color ^ movCh) && (raspChess[x - t - 1][y + t + 1].chess)) : true) {
										break;
									}
									else if (((x - t - 1 >= 0) && (y + t + 1 < 8)) ? (raspChess[x - t][y + t].chess && (raspChess[x - t][y + t].color ^ movCh) && (!raspChess[x - t - 1][y + t + 1].chess)) : false) {
										for (signed int o = t; o < 8; o++) {
											if ((x - o - 1 >= 0) && (y + o + 1 < 8)) {
												if (!raspChess[x - o - 1][y + o + 1].chess) {
													listSost = Addlist (&listSost, raspChess);
													isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x - o - 1, y + o + 1);
													if (isCheckOneStrike ((*(*listSost).last).raspChess, x - o - 1, y + o + 1, movCh)) {
														(*(*listSost).last).dophod = TRUE;
														(*(*listSost).last).sledHod = podborOneHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, x - o - 1, y + o + 1, movCh, vlojen - 2);
													}
													else {
														(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 2);
													}
												}
												else break;
											}
											else {
												break;
											}
										}
										break;
									}
								}
								for (signed int t = 1; t < 8; t++) {
									if (((x + t < 8) && (y + t < 8)) ? ((raspChess[x + t][y + t].chess) && (raspChess[x + t][y + t].color == movCh)) : true) {
										break;
									}
									else if (((x + t + 1 < 8) && (y + t + 1 < 8)) ? (raspChess[x + t][y + t].chess && (raspChess[x + t][y + t].color ^ movCh) && (raspChess[x + t + 1][y + t + 1].chess)) : true) {
										break;
									}
									else if (((x + t + 1 < 8) && (y + t + 1 < 8)) ? (raspChess[x + t][y + t].chess && (raspChess[x + t][y + t].color ^ movCh) && (!raspChess[x + t + 1][y + t + 1].chess)) : false) {
										for (signed int o = t; o < 8; o++) {
											if ((x + o + 1 < 8) && (y + o + 1 < 8)) {
												if (!raspChess[x + o + 1][y + o + 1].chess) {
													listSost = Addlist (&listSost, raspChess);
													isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x + o + 1, y + o + 1);
													if (isCheckOneStrike ((*(*listSost).last).raspChess, x + o + 1, y + o + 1, movCh)) {
														(*(*listSost).last).dophod = TRUE;
														(*(*listSost).last).sledHod = podborOneHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, x + o + 1, y + o + 1, movCh, vlojen - 2);
													}
													else {
														(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 2);
													}
												}
												else break;
											}
											else {
												break;
											}
										}
										break;
									}
								}
							}
						}
					}
				}
			}
		}
		else {
			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {
					if (x < 8 && y < 8 && ((x % 2) ^ (y % 2))) {
						if (raspChess[x][y].chess) {
							if (!raspChess[x][y].queen) {
								if ((raspChess[x][y].color == WH) && (movCh == WH)) {
									if (((x - 1 >= 0) && (y - 1 >= 0)) ? !(raspChess[x - 1][y - 1].chess) : false) {
										listSost = Addlist (&listSost, raspChess);
										isMove (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x - 1, y - 1);
										(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 1);
									}
									if (((x - 1 >= 0) && (y + 1 < 8)) ? !(raspChess[x - 1][y + 1].chess) : false) {
										listSost = Addlist (&listSost, raspChess);
										isMove (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x - 1, y + 1);
										(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 1);
									}
								}
								if ((raspChess[x][y].color == BL) && (movCh == BL)) {
									if (((x + 1 < 8) && (y - 1 >= 0)) ? !(raspChess[x + 1][y - 1].chess) : false) {
										listSost = Addlist (&listSost, raspChess);
										isMove (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x + 1, y - 1);
										(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 1);
									}
									if (((x + 1 < 8) && (y + 1 < 8)) ? !(raspChess[x + 1][y + 1].chess) : false) {
										listSost = Addlist (&listSost, raspChess);
										isMove (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x + 1, y + 1);
										(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 1);
									}
								}
							}
							else if (raspChess[x][y].queen) {
								if (raspChess[x][y].color == movCh) {
									for (signed int t = 1; t < 8; t++) {
										if (((x - t >= 0) && (y - t >= 0)) ? !(raspChess[x - t][y - t].chess) : false) {
											listSost = Addlist (&listSost, raspChess);
											isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x - t, y - t);
											(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 2);
										}
										else {
											break;
										}
									}
									for (signed int t = 1; t < 8; t++) {
										if (((x + t < 8) && (y - t >= 0)) ? !(raspChess[x + t][y - t].chess) : false) {
											listSost = Addlist (&listSost, raspChess);
											isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x + t, y - t);
											(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 2);
										}
										else {
											break;
										}
									}
									for (signed int t = 1; t < 8; t++) {
										if (((x - t >= 0) && (y + t < 8)) ? !(raspChess[x - t][y + t].chess) : false) {
											listSost = Addlist (&listSost, raspChess);
											isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x - t, y + t);
											(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 2);
										}
										else {
											break;
										}
									}
									for (signed int t = 1; t < 8; t++) {
										if (((x + t < 8) && (y + t < 8)) ? !(raspChess[x + t][y + t].chess) : false) {
											listSost = Addlist (&listSost, raspChess);
											isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x + t, y + t);
											(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 2);
										}
										else {
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else {
		movCh = !movCh;
		return NULL;
	}
	return listSost;
}

aiComp::myList* aiComp::podborOneHodov (myList *listSost, clChess::myChessStruct raspChess[8][8], int x, int y, int movCh, int vlojen) {
	if (vlojen >= 0) {
		if (!raspChess[x][y].queen) {
			if (raspChess[x][y].color == movCh) {
				if (((x - 2 >= 0) && (y - 2 >= 0)) ? (raspChess[x - 1][y - 1].chess && (raspChess[x - 1][y - 1].color ^ movCh) && (!raspChess[x - 2][y - 2].chess)) : false) {
					listSost = Addlist (&listSost, raspChess);
					isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x - 2, y - 2);
					if (isCheckOneStrike ((*(*listSost).last).raspChess, x - 2, y - 2, movCh)) {
						(*(*listSost).last).dophod = TRUE;
						(*(*listSost).last).sledHod = podborOneHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, x - 2, y - 2, movCh, vlojen - 1);
					}
					else {
						(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 1);
					}
				}
				if (((x - 2 >= 0) && (y + 2 < 8)) ? (raspChess[x - 1][y + 1].chess && (raspChess[x - 1][y + 1].color ^ movCh) && (!raspChess[x - 2][y + 2].chess)) : false) {
					listSost = Addlist (&listSost, raspChess);
					isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x - 2, y + 2);
					if (isCheckOneStrike ((*(*listSost).last).raspChess, x - 2, y + 2, movCh)) {
						(*(*listSost).last).dophod = TRUE;
						(*(*listSost).last).sledHod = podborOneHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, x - 2, y + 2, movCh, vlojen - 1);
					}
					else {
						(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 1);
					}
				}
				if (((x + 2 < 8) && (y - 2 >= 0)) ? (raspChess[x + 1][y - 1].chess && (raspChess[x + 1][y - 1].color ^ movCh) && (!raspChess[x + 2][y - 2].chess)) : false) {
					listSost = Addlist (&listSost, raspChess);
					isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x + 2, y - 2);
					if (isCheckOneStrike ((*(*listSost).last).raspChess, x + 2, y - 2, movCh)) {
						(*(*listSost).last).dophod = TRUE;
						(*(*listSost).last).sledHod = podborOneHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, x + 2, y - 2, movCh, vlojen - 1);
					}
					else {
						(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 1);
					}
				}
				if (((x + 2 < 8) && (y + 2 < 8)) ? (raspChess[x + 1][y + 1].chess && (raspChess[x + 1][y + 1].color ^ movCh) && (!raspChess[x + 2][y + 2].chess)) : false) {
					listSost = Addlist (&listSost, raspChess);
					isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x + 2, y + 2);
					if (isCheckOneStrike ((*(*listSost).last).raspChess, x + 2, y + 2, movCh)) {
						(*(*listSost).last).dophod = TRUE;
						(*(*listSost).last).sledHod = podborOneHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, x + 2, y + 2, movCh, vlojen - 1);
					}
					else {
						(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 1);
					}
				}
			}
		}
		else if (raspChess[x][y].queen) {
			if (raspChess[x][y].color == movCh) {
				for (signed int t = 1; t < 8; t++) {
					if (((x - t >= 0) && (y - t >= 0)) ? ((raspChess[x - t][y - t].chess) && (raspChess[x - t][y - t].color == movCh)) : true) {
						break;
					}
					else if (((x - t - 1 >= 0) && (y - t - 1 >= 0)) ? (raspChess[x - t][y - t].chess && (raspChess[x - t][y - t].color ^ movCh) && (raspChess[x - t - 1][y - t - 1].chess)) : true) {
						break;
					}
					else if (((x - t - 1 >= 0) && (y - t - 1 >= 0)) ? (raspChess[x - t][y - t].chess && (raspChess[x - t][y - t].color ^ movCh) && (!raspChess[x - t - 1][y - t - 1].chess)) : false) {
						for (signed int o = t; o < 8; o++) {
							if ((x - o - 1 >= 0) && (y - o - 1 >= 0)) {
								if (!raspChess[x - o - 1][y - o - 1].chess) {
									listSost = Addlist (&listSost, raspChess);
									isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x - o - 1, y - o - 1);
									if (isCheckOneStrike ((*(*listSost).last).raspChess, x - o - 1, y - o - 1, movCh)) {
										(*(*listSost).last).dophod = TRUE;
										(*(*listSost).last).sledHod = podborOneHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, x - o - 1, y - o - 1, movCh, vlojen - 2);
									}
									else {
										(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 2);
									}
								}
								else break;
							}
							else {
								break;
							}
						}
						break;
					}
				}
				for (signed int t = 1; t < 8; t++) {
					if (((x + t < 8) && (y - t >= 0)) ? ((raspChess[x + t][y - t].chess) && (raspChess[x + t][y - t].color == movCh)) : true) {
						break;
					}
					else if (((x + t + 1 < 8) && (y - t - 1 >= 0)) ? (raspChess[x + t][y - t].chess && (raspChess[x + t][y - t].color ^ movCh) && (raspChess[x + t + 1][y - t - 1].chess)) : true) {
						break;
					}
					else if (((x + t + 1 < 8) && (y - t - 1 >= 0)) ? (raspChess[x + t][y - t].chess && (raspChess[x + t][y - t].color ^ movCh) && (!raspChess[x + t + 1][y - t - 1].chess)) : false) {
						for (signed int o = t; o < 8; o++) {
							if ((x + o + 1 < 8) && (y - o - 1 >= 0)) {
								if (!raspChess[x + o + 1][y - o - 1].chess) {
									listSost = Addlist (&listSost, raspChess);
									isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x + o + 1, y - o - 1);
									if (isCheckOneStrike ((*(*listSost).last).raspChess, x + o + 1, y - o - 1, movCh)) {
										(*(*listSost).last).dophod = TRUE;
										(*(*listSost).last).sledHod = podborOneHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, x + o + 1, y - o - 1, movCh, vlojen - 2);
									}
									else {
										(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 2);
									}
								}
								else break;
							}
							else {
								break;
							}
						}
						break;
					}
				}
				for (signed int t = 1; t < 8; t++) {
					if (((x - t >= 0) && (y + t < 8)) ? ((raspChess[x - t][y + t].chess) && (raspChess[x - t][y + t].color == movCh)) : true) {
						break;
					}
					else if (((x - t - 1 >= 0) && (y + t + 1 < 8)) ? (raspChess[x - t][y + t].chess && (raspChess[x - t][y + t].color ^ movCh) && (raspChess[x - t - 1][y + t + 1].chess)) : true) {
						break;
					}
					else if (((x - t - 1 >= 0) && (y + t + 1 < 8)) ? (raspChess[x - t][y + t].chess && (raspChess[x - t][y + t].color ^ movCh) && (!raspChess[x - t - 1][y + t + 1].chess)) : false) {
						for (signed int o = t; o < 8; o++) {
							if ((x - o - 1 >= 0) && (y + o + 1 < 8)) {
								if (!raspChess[x - o - 1][y + o + 1].chess) {
									listSost = Addlist (&listSost, raspChess);
									isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x - o - 1, y + o + 1);
									if (isCheckOneStrike ((*(*listSost).last).raspChess, x - o - 1, y + o + 1, movCh)) {
										(*(*listSost).last).dophod = TRUE;
										(*(*listSost).last).sledHod = podborOneHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, x - o - 1, y + o + 1, movCh, vlojen - 2);
									}
									else {
										(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 2);
									}
								}
								else break;
							}
							else {
								break;
							}
						}
						break;
					}
				}
				for (signed int t = 1; t < 8; t++) {
					if (((x + t < 8) && (y + t < 8)) ? ((raspChess[x + t][y + t].chess) && (raspChess[x + t][y + t].color == movCh)) : true) {
						break;
					}
					else if (((x + t + 1 < 8) && (y + t + 1 < 8)) ? (raspChess[x + t][y + t].chess && (raspChess[x + t][y + t].color ^ movCh) && (raspChess[x + t + 1][y + t + 1].chess)) : true) {
						break;
					}
					else if (((x + t + 1 < 8) && (y + t + 1 < 8)) ? (raspChess[x + t][y + t].chess && (raspChess[x + t][y + t].color ^ movCh) && (!raspChess[x + t + 1][y + t + 1].chess)) : false) {
						for (signed int o = t; o < 8; o++) {
							if ((x + o + 1 < 8) && (y + o + 1 < 8)) {
								if (!raspChess[x + o + 1][y + o + 1].chess) {
									listSost = Addlist (&listSost, raspChess);
									isStrike (&((*(*listSost).last).ocenka), (*(*listSost).last).raspChess, x, y, x + o + 1, y + o + 1);
									if (isCheckOneStrike ((*(*listSost).last).raspChess, x + o + 1, y + o + 1, movCh)) {
										(*(*listSost).last).dophod = TRUE;
										(*(*listSost).last).sledHod = podborOneHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, x + o + 1, y + o + 1, movCh, vlojen - 2);
									}
									else {
										(*(*listSost).last).sledHod = podborHodov ((*(*listSost).last).sledHod, (*(*listSost).last).raspChess, !movCh, vlojen - 2);
									}
								}
								else break;
							}
							else {
								break;
							}
						}
						break;
					}
				}
			}
		}
	}
	else {
		movCh = !movCh;
		return NULL;
	}
	return listSost;
}


void aiComp::isStrike (int *ocenka, clChess::myChessStruct raspChess[8][8], int x, int y, int xOn, int yOn) {
	raspChess[xOn][yOn] = raspChess[x][y];
	if (((raspChess[xOn][yOn].color == WH) && (xOn == 0)) || ((raspChess[xOn][yOn].color == BL) && (xOn == 7))) {
		raspChess[xOn][yOn].queen = TRUE;
	}
	int k = abs (xOn - x);
	int xG1 = (xOn - x) / abs (xOn - x);
	int yG1 = (yOn - y) / abs (yOn - y);
	for (signed int i = 1; i < k; i++) {
		if (raspChess[x + i*xG1][y + i*yG1].chess) {
			if (raspChess[x + i*xG1][y + i*yG1].queen) {
				if (raspChess[xOn][yOn].color == WH) {
					*ocenka = -200;
				}
				else if (raspChess[xOn][yOn].color == BL) {
					*ocenka = 200;
				}
			}
			else if (!raspChess[x + i*xG1][y + i*yG1].queen) {
				if (raspChess[xOn][yOn].color == WH) {
					*ocenka = -100;
				}
				else if (raspChess[xOn][yOn].color == BL) {
					*ocenka = 100;
				}
			}
		}
		raspChess[x + i*xG1][y + i*yG1].chess = FALSE;
		raspChess[x + i*xG1][y + i*yG1].shine = FALSE;
		raspChess[x + i*xG1][y + i*yG1].queen = FALSE;
		raspChess[x + i*xG1][y + i*yG1].color = 2;
	}

	raspChess[x][y].chess = FALSE;
	raspChess[x][y].shine = FALSE;
	raspChess[x][y].queen = FALSE;
	raspChess[x][y].color = 2;
}

void aiComp::isMove (int *ocenka, clChess::myChessStruct raspChess[8][8], int x, int y, int xOn, int yOn) {
	if (raspChess[x][y].color == WH) {
		if (!raspChess[x][y].queen) {
			if (xOn == 0) {
				*ocenka -= 30;
			}
			else  if (xOn == 6) {
				*ocenka -= 1;
			}
		}
		if ((xOn == 4) && (yOn > y) && (y <= 3)) {
			*ocenka -= 29;
		}
		else if ((xOn == 4) && (yOn > y) && (y > 3)) {
			*ocenka -= 50;
		}
		else if ((xOn == 4) && (yOn < y) && (y <= 3)) {
			*ocenka -= 49;
		}
		else if ((xOn == 4) && (yOn < y) && (y > 3)) {
			*ocenka -= 30;
		}
		else if ((yOn > y) && (y <= 3)) {
			*ocenka -= 27;
		}
		else if ((yOn > y) && (y > 3)) {
			*ocenka -= 48;
		}
		else if ((yOn < y) && (y <= 3)) {
			*ocenka -= 47;
		}
		else if ((yOn < y) && (y > 3)) {
			*ocenka -= 28;
		}
	}
	else if (raspChess[x][y].color == BL) {
		if (!raspChess[x][y].queen) {
			if (xOn == 7) {
				*ocenka += 30;
			}
			else if (xOn == 1) {
				*ocenka += 1;
			}
		}
		if ((xOn == 3) && (yOn > y) && (y <= 3)) {
			*ocenka += 29;
		}
		else if ((xOn == 3) && (yOn > y) && (y > 3)) {
			*ocenka += 50;
		}
		else if ((xOn == 3) && (yOn < y) && (y <= 3)) {
			*ocenka += 49;
		}
		else if ((xOn == 3) && (yOn < y) && (y > 3)) {
			*ocenka += 30;
		}
		else if ((yOn > y) && (y <= 3)) {
			*ocenka += 27;
		}
		else if ((yOn > y) && (y > 3)) {
			*ocenka += 48;
		}
		else if ((yOn < y) && (y <= 3)) {
			*ocenka += 47;
		}
		else if ((yOn < y) && (y > 3)) {
			*ocenka += 28;
		}
	}
	raspChess[xOn][yOn] = raspChess[x][y];
	if (((raspChess[xOn][yOn].color == WH) && (xOn == 0)) || ((raspChess[xOn][yOn].color == BL) && (xOn == 7))) {
		raspChess[xOn][yOn].queen = TRUE;
	}
	raspChess[x][y].chess = FALSE;
	raspChess[x][y].shine = FALSE;
	raspChess[x][y].queen = FALSE;
	raspChess[x][y].color = 2;
}

BOOL aiComp::isCheckOneStrike (clChess::myChessStruct raspChess[8][8], int i, int j, int movCh) {
	BOOL vihodn = FALSE;
	if (!raspChess[i][j].queen) {
		if ((((i - 2 >= 0) && (j - 2 >= 0)) ? (raspChess[i - 1][j - 1].chess && (raspChess[i - 1][j - 1].color ^ movCh) && (!raspChess[i - 2][j - 2].chess)) : false) ||
			(((i - 2 >= 0) && (j + 2 < 8)) ? (raspChess[i - 1][j + 1].chess && (raspChess[i - 1][j + 1].color ^ movCh) && (!raspChess[i - 2][j + 2].chess)) : false) ||
			(((i + 2 < 8) && (j - 2 >= 0)) ? (raspChess[i + 1][j - 1].chess && (raspChess[i + 1][j - 1].color ^ movCh) && (!raspChess[i + 2][j - 2].chess)) : false) ||
			(((i + 2 < 8) && (j + 2 < 8)) ? (raspChess[i + 1][j + 1].chess && (raspChess[i + 1][j + 1].color ^ movCh) && (!raspChess[i + 2][j + 2].chess)) : false)) {
			raspChess[i][j].necesStrike = TRUE;
			vihodn = TRUE;
		}
	}
	else if (raspChess[i][j].queen) {
		for (signed int t = 1; t < 8; t++) {
			if (((i - t > 0) && (j - t > 0)) ? ((raspChess[i - t][j - t].chess) && (raspChess[i - t][j - t].color == movCh)) : true) {
				break;
			}
			else if (((i - t - 1 >= 0) && (j - t - 1 >= 0)) ? (raspChess[i - t][j - t].chess && (raspChess[i - t][j - t].color ^ movCh) && (raspChess[i - t - 1][j - t - 1].chess)) : true) {
				break;
			}
			else if (((i - t - 1 >= 0) && (j - t - 1 >= 0)) ? (raspChess[i - t][j - t].chess && (raspChess[i - t][j - t].color ^ movCh) && (!raspChess[i - t - 1][j - t - 1].chess)) : false) {
				raspChess[i][j].necesStrike = TRUE;
				vihodn = TRUE;
				break;
			}
		}
		for (signed int t = 1; t < 8; t++) {
			if (((i + t < 8) && (j - t > 0)) ? ((raspChess[i + t][j - t].chess) && (raspChess[i + t][j - t].color == movCh)) : true) {
				break;
			}
			else if (((i + t + 1 < 8) && (j - t - 1 >= 0)) ? (raspChess[i + t][j - t].chess && (raspChess[i + t][j - t].color ^ movCh) && (raspChess[i + t + 1][j - t - 1].chess)) : true) {
				break;
			}
			else if (((i + t + 1 < 8) && (j - t - 1 >= 0)) ? (raspChess[i + t][j - t].chess && (raspChess[i + t][j - t].color ^ movCh) && (!raspChess[i + t + 1][j - t - 1].chess)) : false) {
				raspChess[i][j].necesStrike = TRUE;
				vihodn = TRUE;
				break;
			}
		}
		for (signed int t = 1; t < 8; t++) {
			if (((i - t > 0) && (j + t < 8)) ? ((raspChess[i - t][j + t].chess) && (raspChess[i - t][j + t].color == movCh)) : true) {
				break;
			}
			else if (((i - t - 1 >= 0) && (j + t + 1 < 8)) ? (raspChess[i - t][j + t].chess && (raspChess[i - t][j + t].color ^ movCh) && (raspChess[i - t - 1][j + t + 1].chess)) : true) {
				break;
			}
			else if (((i - t - 1 >= 0) && (j + t + 1 < 8)) ? (raspChess[i - t][j + t].chess && (raspChess[i - t][j + t].color ^ movCh) && (!raspChess[i - t - 1][j + t + 1].chess)) : false) {
				raspChess[i][j].necesStrike = TRUE;
				vihodn = TRUE;
				break;
			}
		}
		for (signed int t = 1; t < 8; t++) {
			if (((i + t < 8) && (j + t < 8)) ? ((raspChess[i + t][j + t].chess) && (raspChess[i + t][j + t].color == movCh)) : true) {
				break;
			}
			else if (((i + t + 1 < 8) && (j + t + 1 < 8)) ? (raspChess[i + t][j + t].chess && (raspChess[i + t][j + t].color ^ movCh) && (raspChess[i + t + 1][j + t + 1].chess)) : true) {
				break;
			}
			else if (((i + t + 1 < 8) && (j + t + 1 < 8)) ? (raspChess[i + t][j + t].chess && (raspChess[i + t][j + t].color ^ movCh) && (!raspChess[i + t + 1][j + t + 1].chess)) : false) {
				raspChess[i][j].necesStrike = TRUE;
				vihodn = TRUE;
				break;
			}
		}
	}
	return vihodn;
}

BOOL aiComp::isCheckStrike (clChess::myChessStruct raspChess[8][8], int movCh) {
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
				if (raspChess[i][j].color == movCh) {
					if (raspChess[i][j].chess) {
						if (!raspChess[i][j].queen) {
							if ((((i - 2 >= 0) && (j - 2 >= 0)) ? (raspChess[i - 1][j - 1].chess && (raspChess[i - 1][j - 1].color ^ movCh) && (!raspChess[i - 2][j - 2].chess)) : false) ||
								(((i - 2 >= 0) && (j + 2 < 8)) ? (raspChess[i - 1][j + 1].chess && (raspChess[i - 1][j + 1].color ^ movCh) && (!raspChess[i - 2][j + 2].chess)) : false) ||
								(((i + 2 < 8) && (j - 2 >= 0)) ? (raspChess[i + 1][j - 1].chess && (raspChess[i + 1][j - 1].color ^ movCh) && (!raspChess[i + 2][j - 2].chess)) : false) ||
								(((i + 2 < 8) && (j + 2 < 8)) ? (raspChess[i + 1][j + 1].chess && (raspChess[i + 1][j + 1].color ^ movCh) && (!raspChess[i + 2][j + 2].chess)) : false)) {
								raspChess[i][j].necesStrike = TRUE;
								vihodn = TRUE;
							}
						}
						else if (raspChess[i][j].queen) {
							for (signed int t = 1; t < 8; t++) {
								if (((i - t > 0) && (j - t > 0)) ? ((raspChess[i - t][j - t].chess) && (raspChess[i - t][j - t].color == movCh)) : true) {
									break;
								}
								else if (((i - t - 1 >= 0) && (j - t - 1 >= 0)) ? (raspChess[i - t][j - t].chess && (raspChess[i - t][j - t].color ^ movCh) && (raspChess[i - t - 1][j - t - 1].chess)) : true) {
									break;
								}
								else if (((i - t - 1 >= 0) && (j - t - 1 >= 0)) ? (raspChess[i - t][j - t].chess && (raspChess[i - t][j - t].color ^ movCh) && (!raspChess[i - t - 1][j - t - 1].chess)) : false) {
									raspChess[i][j].necesStrike = TRUE;
									vihodn = TRUE;
									break;
								}
							}
							for (signed int t = 1; t < 8; t++) {
								if (((i + t < 8) && (j - t > 0)) ? ((raspChess[i + t][j - t].chess) && (raspChess[i + t][j - t].color == movCh)) : true) {
									break;
								}
								else if (((i + t + 1 < 8) && (j - t - 1 >= 0)) ? (raspChess[i + t][j - t].chess && (raspChess[i + t][j - t].color ^ movCh) && (raspChess[i + t + 1][j - t - 1].chess)) : true) {
									break;
								}
								else if (((i + t + 1 < 8) && (j - t - 1 >= 0)) ? (raspChess[i + t][j - t].chess && (raspChess[i + t][j - t].color ^ movCh) && (!raspChess[i + t + 1][j - t - 1].chess)) : false) {
									raspChess[i][j].necesStrike = TRUE;
									vihodn = TRUE;
									break;
								}
							}
							for (signed int t = 1; t < 8; t++) {
								if (((i - t > 0) && (j + t < 8)) ? ((raspChess[i - t][j + t].chess) && (raspChess[i - t][j + t].color == movCh)) : true) {
									break;
								}
								else if (((i - t - 1 >= 0) && (j + t + 1 < 8)) ? (raspChess[i - t][j + t].chess && (raspChess[i - t][j + t].color ^ movCh) && (raspChess[i - t - 1][j + t + 1].chess)) : true) {
									break;
								}
								else if (((i - t - 1 >= 0) && (j + t + 1 < 8)) ? (raspChess[i - t][j + t].chess && (raspChess[i - t][j + t].color ^ movCh) && (!raspChess[i - t - 1][j + t + 1].chess)) : false) {
									raspChess[i][j].necesStrike = TRUE;
									vihodn = TRUE;
									break;
								}
							}
							for (signed int t = 1; t < 8; t++) {
								if (((i + t < 8) && (j + t < 8)) ? ((raspChess[i + t][j + t].chess) && (raspChess[i + t][j + t].color == movCh)) : true) {
									break;
								}
								else if (((i + t + 1 < 8) && (j + t + 1 < 8)) ? (raspChess[i + t][j + t].chess && (raspChess[i + t][j + t].color ^ movCh) && (raspChess[i + t + 1][j + t + 1].chess)) : true) {
									break;
								}
								else if (((i + t + 1 < 8) && (j + t + 1 < 8)) ? (raspChess[i + t][j + t].chess && (raspChess[i + t][j + t].color ^ movCh) && (!raspChess[i + t + 1][j + t + 1].chess)) : false) {
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

void aiComp::copy (clChess::myChessStruct oneMass[8][8], clChess::myChessStruct twoMass[8][8]) {
	for (size_t i = 0; i < 8; i++) {
		for (size_t j = 0; j < 8; j++) {
			oneMass[i][j] = twoMass[i][j];
		}
	}
}


void aiComp::poiskHoda (myList *listSost, clChess::myChessStruct raspChess[8][8], int podschet, BOOL prover) {
	myList::mySpHodov *dopHod;
	if (listSost != NULL) {
		dopHod = (*listSost).first;
		while (dopHod != NULL) {
			if (prover) {
				copy (hodComp, (*dopHod).raspChess);
			}
			poiskHoda ((*dopHod).sledHod, raspChess, podschet + (*dopHod).ocenka, prover ? ((*dopHod).dophod ? TRUE: FALSE) : FALSE);
			dopHod = (*dopHod).next;
		}
	}
	else if (listSost == NULL) {
		if (maxSum < podschet) {
			maxSum = podschet;
			copy (raspChess, hodComp);
		}
	}
}