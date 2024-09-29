.PHONY: all clean run_client

all:
	$(MAKE) -C src all

clean:
	$(MAKE) -C src clean

run_client:
	$(MAKE) -C src run_client
