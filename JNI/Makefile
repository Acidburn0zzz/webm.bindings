JAVA_HOME=/usr/local/buildtools/java/jdk6

CXXFLAGS := -m64 -fPIC -Ilibvpx -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux

quiet?=true
quiet:=$(if $(verbose),,true)
qexec=$(if $(quiet), @)

objects := $(patsubst %.cc,obj/%.o,$(wildcard *.cc))

final_class := Application

$(final_class): libvpxJNI.so $(final_class).class

libvpxJNI.so: $(objects) x64/libvpx.a
	$(qexec)$(CXX) $(CXXFLAGS) -shared $^ -o $@

%.class : %.java $(shell find com/ -type f -name '*.java')
	$(qexec)javac -Xlint:unchecked $<

obj/%.o : %.cc
	$(qexec)mkdir -p $(dir $@)
	$(qexec)$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(qexec)$(RM) $(shell find . -type f -name '*.class') libvpxJNI.so $(objects)

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
