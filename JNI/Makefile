JAVA_HOME := /usr/local/buildtools/java/jdk6-64
CFLAGS := -DNDEBUG -fPIC -O2 -m64
CXXFLAGS := -DNDEBUG -fPIC -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux \
	-O2 -m64
JAVA := $(JAVA_HOME)/bin/java
JAVA_ARGS := -cp class -Djava.library.path=.
JAVAC := $(JAVA_HOME)/bin/javac
JAVAC_COMPILERARGS := -d class
LDFLAGS := -fPIC -shared

vorbis_c_sources := $(wildcard vorbis/*.cc)
vorbis_c_objects := $(patsubst %.cc,obj/%.o,$(vorbis_c_sources))
vorbis_java_sources := $(wildcard com/google/libvorbis/*.java)
vorbis_java_classes := $(patsubst %.java,class/%.class,$(vorbis_java_sources))

vpx_c_sources := $(wildcard vpx/*.cc)
vpx_c_objects := $(patsubst %.cc,obj/%.o,$(vpx_c_sources))
vpx_java_sources := $(wildcard com/google/libvpx/*.java)
vpx_java_classes := $(patsubst %.java,class/%.class,$(vpx_java_sources))

webm_c_sources := $(shell find webm/ -name "*.cc" -type f)
webm_c_objects := $(patsubst %.cc,obj/%.o,$(webm_c_sources))
webm_java_sources := $(shell find com/google/libwebm/ -name "*.java" -type f)
webm_java_classes := $(patsubst %.java,class/%.class,$(webm_java_sources))
ebml_writer := obj/libvpx/libmkv/EbmlWriter.o

classes := $(vorbis_java_classes) $(vpx_java_classes) $(webm_java_classes)
libraries := libvorbisJNI.so libvpxJNI.so libwebmJNI.so
deps := $(classes) $(libraries)

export LD_LIBRARY_PATH += libwebm

.PHONY: run_app
run_app: Application $(deps)
	$(JAVA) $(JAVA_ARGS) $<

.PHONY: run_muxer
run_muxer: SampleMultiplexer $(deps)
	$(JAVA) $(JAVA_ARGS) $< -i input/small.webm -o output/small_out.webm

.PHONY: display
display: output/foreman_cif_420p_352x288.ivf
	libvpx/vpxdec --i420 --limit=1 \
		--output=output/foreman_cif_420p_352x288.yuv \
		output/foreman_cif_420p_352x288.ivf
	display -size 352x288 -depth 8 \
		-colorspace RGB output/foreman_cif_420p_352x288.yuv

.PHONY: play
play: output/foreman_cif_420p_352x288.ivf
	libvpx/vpxdec \
		--output=output/foreman_cif_420p_352x288.y4m \
		output/foreman_cif_420p_352x288.ivf
	mplayer output/foreman_cif_420p_352x288.y4m

Application: class/Application.class

SampleMultiplexer: class/SampleMultiplexer.class

libvorbisJNI.so: $(vorbis_c_objects)
	$(CXX) $(LDFLAGS) -lvorbis -o $@ $(vorbis_c_objects)

libvpxJNI.so: $(vpx_c_objects) $(ebml_writer)
	$(CXX) $(LDFLAGS) -lvpx -o $@ $(vpx_c_objects) $(ebml_writer)

libwebmJNI.so: $(webm_c_objects)
	$(CXX) $(LDFLAGS) -lwebm -Llibwebm -o $@ $(webm_c_objects)

$(vorbis_c_objects): obj/%.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -Ilibogg/include -Ilibvorbis/include -o $@ $<

$(vpx_c_objects): obj/%.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -Ilibvpx -o $@ $<

$(webm_c_objects): obj/%.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -Ilibwebm -Iwebm -o $@ $<

class/%.class: %.java
	mkdir -p $(dir $@)
	$(JAVAC) $(JAVAC_COMPILERARGS) $<

$(ebml_writer): obj/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -Ilibvpx -o $@ $<

.PHONY: clean
clean:
	$(RM) $(libraries)
	$(RM) -r class obj
