INCLUDES = \
	./impl \
	./test \
	./

CXX := g++
CXXFLAGS := -Wall -std=c++17 $(addprefix -I, $(INCLUDES))
TEST_TARGETS:= build/test_thread_simple build/test_thread_cv build/test_singleton build/test_100_cnumbers
TARGETS := build/sim_osi_stack
MAIN_SRCS := osi_launcher.cpp
TEST_STHREAD_SRCS := test/test_thread_simple.cpp
TEST_CVTHREAD_SRCS := test/test_thread_cv.cpp
TEST_SINGLETON_SRCS := test/test_singleton.cpp osi_impl/network_params.cpp
TEST_100_NUMBERS_SRCS := test/test_100_concur_numbers.cpp
#OBJS = $(SRCS:.cpp=.o)

all: $(TARGETS)

tests: CXXFLAGS+=-DTEST
tests: $(TEST_TARGETS)

build/sim_osi_stack: $(MAIN_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

build/test_thread_simple: $(TEST_STHREAD_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

build/test_thread_cv: $(TEST_CVTHREAD_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

build/test_singleton: $(TEST_SINGLETON_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

build/test_100_cnumbers: $(TEST_100_NUMBERS_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

#$(TARGETS): $(OBJS)
#	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

#%o: %.cpp
#	$(CXX) $(CXXFLAGS) -c $< -o $@

#clean:
#	rm -rf $(TARGET) $(OBJS)

clean:
	rm -rf $(TARGETS) *.o
	rm -rf $(TEST_TARGETS) *.o

.PHONY: all clean