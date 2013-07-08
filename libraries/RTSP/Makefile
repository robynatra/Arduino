

INC = -I./inc -I./3rd  
LIBS = 
CFLAGS = -g #-std=c++0x

OBJECTS =   \
RtspRequestInterface.o \
RtspRequest.o \
RTSPProtocol.o \
StrPtrLen.o \
StringParser.o \
StringTranslator.o 


TEST_OBJECTS = rtsp_test.o $(OBJECTS) 


all: rtsp_test 

rtsp_test:$(TEST_OBJECTS) 
	g++ $(CFLAGS) -o rtsp_test  $(TEST_OBJECTS) $(INC) $(LIBS)

%.o:src/%.cpp
	g++ $(CFLAGS)  -c -o $@ $< $(INC)
%.o:3rd/%.cpp
	g++ $(CFLAGS)  -c -o $@ $< $(INC)



clean:
	rm *.o rtsp_test 
