Compilador= g++
NAME= parallelBinarization

 #$@    Nome da regra. 
 #$<    Nome da primeira dependência 
 #$^     Lista de dependências
 #$?     Lista de dependências mais recentes que a regra.
 #$*     Nome do arquivo sem sufixo

### include O level optimization : 0-3
OPT?= 3

BINDIR= bin
INCDIR= inc
SRCDIR= src
OBJDIR= obj

LIBS= -fopenmp -lpthread

SRC=    $(wildcard $(SRCDIR)/*.cpp)
OBJ=    $(SRC:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o$(SUFFIX))
BIN=    $(BINDIR)/$(NAME)

all: clean objdir_mk bindir_mk bin

clean:
	@echo 'Removendo todos os objetos'
	@rm -rf $(OBJDIR)
	@echo 'Removendo todos os binários'
	@rm -f $(BINDIR)/*

bin:    $(OBJ)
	@echo
	@echo 'Criando binários "$(BIN)"'
	@$(Compilador) -o $(BIN) $(OBJ) $(LIBS)
	@echo '... Saindo'
	@echo
	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo 'Compilando arquivo objeto "$@" ...'
	@$(Compilador) -c -o $@ $(FLAGS) $<

bindir_mk:
	@echo 'Criando a pasta $(BINDIR) ...'
	@mkdir -p $(BINDIR)
	
objdir_mk:
	@echo
	@echo 'Criando a pasta $(OBJDIR) ...'
	@mkdir -p $(OBJDIR)

run:
	@echo '1º teste'
	./$(BIN) -in /home/pargles/Documentos/disco -inf -vf -bl
