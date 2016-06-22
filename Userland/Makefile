include Makefile.inc

SAMPLE_DATA=fractalDataModule.bin
FRACTAL_SOURCE=sierpinski_params

all: sampleCodeModule fractalDataModule

sampleCodeModule:
	cd SampleCodeModule; make

fractalDataModule:
	rm -rf $(SAMPLE_DATA)
    cat $(FRACTAL_DATA) >> $(SAMPLE_DATA) && dd if=/dev/zero bs=1 count=1 >> $(SAMPLE_DATA)

clean:
	cd SampleCodeModule; make clean
	rm -rf *.bin


.PHONY: sampleCodeModule all clean
