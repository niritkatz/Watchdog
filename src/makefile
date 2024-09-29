CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -g -I../inc/ -I../utils/ds/inc/
LDFLAGS=-pthread
SRCDIR=../utils/ds/src
OBJDIR=obj
CLIENT_SOURCES=wd_client.c wd.c $(SRCDIR)/scheduler.c $(SRCDIR)/pqueue.c $(SRCDIR)/task.c $(SRCDIR)/uid.c $(SRCDIR)/dvector.c $(SRCDIR)/heap.c
PROC_SOURCES=wd_proc.c wd.c $(SRCDIR)/scheduler.c $(SRCDIR)/pqueue.c $(SRCDIR)/task.c $(SRCDIR)/uid.c $(SRCDIR)/dvector.c $(SRCDIR)/heap.c
CLIENT_OBJECTS=$(addprefix $(OBJDIR)/,$(notdir $(CLIENT_SOURCES:.c=.o)))
PROC_OBJECTS=$(addprefix $(OBJDIR)/,$(notdir $(PROC_SOURCES:.c=.o)))
EXECUTABLES=wd_client wd_proc

# Compilation only
all: $(EXECUTABLES)

wd_client: $(CLIENT_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

wd_proc: $(PROC_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run client after compilation
run: wd_client
	./wd_client ./wd_client

.PHONY: clean

clean:
	rm -rf $(OBJDIR) $(EXECUTABLES)
