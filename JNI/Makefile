JAVA_HOME=/usr/local/buildtools/java/jdk6-64
JAVA := $(JAVA_HOME)/bin/java
JAVAC := $(JAVA_HOME)/bin/javac

CXXFLAGS := -O2 -DNDEBUG -m64 -fPIC -Ilibvpx -Ilibwebm -Iwebm -Llibwebm
CXXFLAGS += -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux
CFLAGS := -O2 -DNDEBUG -m64 -Ilibvpx -fPIC

export LD_LIBRARY_PATH += /usr/local/lib:libwebm

# Comment out the following line to see more information during a build.
quiet=true
qexec=$(if $(quiet), @)

final_class := Application

vpx_objects := $(patsubst %.cc,obj/%.o,$(wildcard vpx/*.cc))
vpx_objects += $(patsubst %.c,obj/%.o,libvpx/libmkv/EbmlWriter.c)

vorbis_objects := $(patsubst %.cc,obj/%.o,$(wildcard vorbis/*.cc))

webm_source_files = $(shell find webm/ -type f -name '*.cc')
webm_objects := $(patsubst %.cc,obj/%.o,$(wildcard $(webm_source_files)))

objects := $(vpx_objects) $(vorbis_objects) $(webm_objects)

java_files = $(shell find com/ -type f -name '*.java')
classes := $(patsubst %.java,%.class,$(java_files))
classes += $(final_class).class

$(final_class): libvpxJNI.so libvorbisJNI.so libwebmJNI.so $(classes)

SampleMultiplexer.class: libvpxJNI.so libvorbisJNI.so libwebmJNI.so $(classes)

libvpxJNI.so: $(vpx_objects)
	$(qexec)$(CXX) $(CXXFLAGS) -shared $(vpx_objects) -o $@ -lvpx

libvorbisJNI.so: $(vorbis_objects)
	$(qexec)$(CXX) $(CXXFLAGS) -shared $(vorbis_objects) -o $@ -lvorbis

libwebmJNI.so: $(webm_objects)
	$(qexec)$(CXX) $(CXXFLAGS) -shared $(webm_objects) -o $@ -lwebm

%.class : %.java $(java_files)
	$(qexec)$(JAVAC) $<

obj/%.o : %.cc
	$(qexec)mkdir -p $(dir $@)
	$(qexec)$(CXX) $(CXXFLAGS) -c $< -o $@

obj/%.o : %.c
	$(qexec)mkdir -p $(dir $@)
	$(qexec)$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(qexec)$(RM) libvpxJNI.so libvorbisJNI.so libwebmJNI.so $(objects) $(classes)

.PHONY: run
run: $(final_class)
	$(qexec)$(JAVA) -Djava.library.path=`pwd` $<

.PHONY: run_sample
run_sample: SampleMultiplexer.class
	$(qexec)$(JAVA) -Djava.library.path=`pwd` SampleMultiplexer -i input/small.webm -o output/small_out.webm

.PHONY: display
display: output/foreman_cif_420p_352x288.ivf
	$(qexec)libvpx/vpxdec --i420 --limit=1 \
		--output=output/foreman_cif_420p_352x288.yuv \
		output/foreman_cif_420p_352x288.ivf
	$(qexec)display -size 352x288 -depth 8 \
		-colorspace RGB output/foreman_cif_420p_352x288.yuv

.PHONY: play
play: output/foreman_cif_420p_352x288.ivf
	$(qexec)libvpx/vpxdec  \
		--output=output/foreman_cif_420p_352x288.y4m \
		output/foreman_cif_420p_352x288.ivf
	$(qexec)mplayer output/foreman_cif_420p_352x288.y4m
