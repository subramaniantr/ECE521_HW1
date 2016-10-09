CC = gcc
CFLAGS=	-g
CSRC=	main.c utils.c res.c isrc.c vsrc.c vcvs.c vccs.c ccvs.c cccs.c dio.c tf.c gyro.c
COBJ=	main.o utils.o res.o isrc.o vsrc.o vcvs.o vccs.o ccvs.o cccs.o dio.o tf.o gyro.o

.c.o:	${CSRC}
	${CC} ${CFLAGS} -c $*.c
myspice: ${COBJ} 
	${CC} ${CFLAGS} -o myspice ${COBJ} -lm
clean:
	rm myspice ${COBJ}
