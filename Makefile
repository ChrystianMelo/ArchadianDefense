# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -I./include/
LDFLAGS = -L /usr/local/lib -lboost_unit_test_framework

# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

# Coleta todos os arquivos fonte, exceto Main.cpp para testes
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
SOURCES_NO_MAIN = $(filter-out $(SRC_DIR)/Main.cpp, $(SOURCES))
OBJECTS_NO_MAIN = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES_NO_MAIN))

TEST_SOURCES = $(wildcard $(TEST_DIR)/test_*.cpp)
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(TEST_SOURCES))

# Executáveis
EXECUTABLE = $(BIN_DIR)/run.out
TEST_EXECUTABLE = $(BIN_DIR)/run_test.out

# Criação dos diretórios, se não existirem
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Alvo padrão: compilar o programa principal
all: $(BIN_DIR) $(OBJ_DIR) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Alvo de teste: compilar e executar os testes, sem compilar Main.cpp
test: $(TEST_SOURCES) $(OBJ_DIR) $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS_NO_MAIN) $(TEST_SOURCES) -o $(TEST_EXECUTABLE) $(LDFLAGS)
	./$(TEST_EXECUTABLE)

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpar os arquivos compilados
clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE) $(TEST_EXECUTABLE)
	rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: all clean test
