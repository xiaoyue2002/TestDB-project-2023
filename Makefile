CC := g++
CFLAGS := -Wall -g 
TARGET := testdb
CFLAGS := -Wall -g -std=c++17 -I ./linux_runtime/usr/local/include/antlr4-runtime
# CFLAGS += -I ./linux_runtime
SRC_DIRS := ./src/filesystem/utils ./src/query ./src/db_manage ./src/record_manage ./src/parser ./src/frontend.cpp ./src/table ./src/index #./test/test_db.cpp
# LDFLAGS := -L ./linux_runtime/usr/local/lib -lantlr4-runtime
LDFLAGS := -L./linux_runtime/usr/local/lib ./linux_runtime/usr/local/lib/libantlr4-runtime.a
# 找到所有的.cpp文件
SRCS := $(shell find $(SRC_DIRS) -name *.cpp)

# 将.cpp文件转换为.o文件
OBJS := $(SRCS:.cpp=.o)

# 构建目标
all: $(TARGET)

# 链接目标
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# 从.cpp生成.o文件的规则
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# 清理构建
clean:
	rm -f $(OBJS) $(TARGET)
