JAVA_HOME=/usr/local/buildtools/java/jdk6

CXXFLAGS := -O2 -DNDEBUG -m64 -fPIC -Ilibvpx
CXXFLAGS += -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -Ix64
CFLAGS := -O2 -DNDEBUG -m64 -Ilibvpx -fPIC

quiet?=true
quiet:=$(if $(verbose),,true)
qexec=$(if $(quiet), @)

final_class := Application

objects := $(patsubst %.cc,obj/%.o,$(wildcard *.cc))
objects += $(patsubst %.c,obj/%.o,libvpx/libmkv/EbmlWriter.c)

java_files = $(shell find com/ -type f -name '*.java')
classes := $(patsubst %.java,%.class,$(java_files))
classes += $(final_class).class

$(final_class): libvpxJNI.so $(classes)

libvpxJNI.so: $(objects) x64/libvpx.so
	$(qexec)$(CXX) $(CXXFLAGS) -shared $(objects) -o $@ \
		-lvpx -Lx64 -Wl,-rpath,x64

%.class : %.java $(java_files)
	$(qexec)javac $<

obj/%.o : %.cc
	$(qexec)mkdir -p $(dir $@)
	$(qexec)$(CXX) $(CXXFLAGS) -c $< -o $@

obj/%.o : %.c
	$(qexec)mkdir -p $(dir $@)
	$(qexec)$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(qexec)$(RM) libvpxJNI.so $(objects) $(classes)

.PHONY: run
run: $(final_class)
	$(qexec)java -Djava.library.path=`pwd` $<

.PHONY: display
display: output/foreman_cif_420p_352x288.ivf
	$(qexec)x64/vpxdec --i420 --limit=1 \
		--output=output/foreman_cif_420p_352x288.yuv \
		output/foreman_cif_420p_352x288.ivf
	$(qexec)display -size 352x288 -depth 8 \
		-colorspace RGB output/foreman_cif_420p_352x288.yuv

.PHONY: play
play: output/foreman_cif_420p_352x288.ivf
	$(qexec)x64/vpxdec  \
		--output=output/foreman_cif_420p_352x288.y4m \
		output/foreman_cif_420p_352x288.ivf
	$(qexec)mplayer output/foreman_cif_420p_352x288.y4m
