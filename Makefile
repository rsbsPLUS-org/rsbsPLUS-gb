CC = lcc
OPTIONS = -Wl-yp0x143=0x80 -Wl-yn=\"rsbsPLUS-gb\"

TARGETS = main.c tiles/all_s.c

default:	${TARGETS}
	${CC} ${OPTIONS} ${TARGETS} 
