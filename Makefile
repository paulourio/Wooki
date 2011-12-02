CFLAGS = -O2 -g -Wall -I. -Iwooki/lib -Istack

OBJS = wooki/benchmark.o wooki/core.o wooki/helpers.o wooki/info.o \
	wooki/parser.o wooki/parsers.o wooki/runtime.o \
	wooki/tokenizer.o wooki/triggers.o wooki/types.o \
	wooki/wobject.o wooki/ewok/ewok.o  wooki/lib/linkedlist.o \
	stack/stack.o stack/stack_intf.o \
	main.o

TARGET = Wooki

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)
			
run: $(TARGET)
	./$(TARGET)
					
clean:
	rm -f $(OBJS) $(TARGET)

