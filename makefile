main: util.o info.o basic.o def.o env.o interaction.o progress.o sentences.o stats.o strategy.o test.o main_interface.o program.o user.o settings.o factory.o file_system.o
	g++ -o final util.o info.o basic.o def.o env.o interaction.o progress.o sentences.o stats.o strategy.o test.o user.o main_interface.o program.o settings.o factory.o file_system.o
interaction.o: interaction.cpp util.h def.h strategy.h env.h sentences.h
	g++ -c -g interaction.cpp
util.o: util.cpp
	g++ -c -g util.cpp
def.o: def.cpp info.h util.h
	g++ -c -g def.cpp
info.o: info.cpp util.h
	g++ -c -g info.cpp
env.o: env.cpp util.h info.h progress.h stats.h basic.h def.h sentences.h
	g++ -c -g env.cpp
strategy.o: strategy.cpp util.h env.h
	g++ -c -g strategy.cpp
info.o: info.h util.h
	g++ -c -g info.cpp
basic.o: basic.cpp info.h
	g++ -c -g basic.cpp
progress.o: progress.cpp info.h
	g++ -c -g progress.cpp
sentences.o: sentences.cpp info.h
	g++ -c -g sentences.cpp
stats.o: stats.cpp info.h
	g++ -c -g stats.cpp
test.o: test.cpp info.h util.h interaction.h
	g++ -c -g test.cpp
main_interface.o: main_interface.cpp interaction.h test.h
	g++ -c -g main_interface.cpp
program.o: program.cpp info.h interaction.h env.h strategy.h user.h factory.h
	g++ -c -g program.cpp
user.o: user.cpp info.h util.h
	g++ -c -g user.cpp
settings.o: settings.cpp info.h util.h interaction.h
	g++ -c -g settings.cpp
factory.o: factory.cpp env.h strategy.h
	g++ -c -g factory.cpp
file_system.o: file_system.cpp
	g++ -c -g file_system.cpp
clean:
	rm *.o
