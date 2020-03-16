SRC=main3G.C image.C sink.C source.C PNMreader.C PNMwriter.C filter.C logging.C
OBJ=$(SRC:.C=.o)
COMP=compare.C image.C sink.C source.C PNMreader.C PNMwriter.C filter.C logging.C
OCPM=$(COMP:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o proj3G

comp: $(OCPM)
	g++ $(OCPM) -o comp


.C.o: $<
	g++  -g -I. -c $<

clean:
	rm *.o proj3G
