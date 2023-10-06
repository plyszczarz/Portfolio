TASKNO=5
APP=sterowanie-dronem
TASKDIR=${HOME}/edu/po/zad/z${TASKNO}

_start_: obj dat ./${APP}
	rm -f core.* core; ./${APP}

# Tworzy katalog "obj" gdy go nie ma
# 
obj:
	mkdir obj

dat:
	mkdir dat


./${APP}: obj/main.o obj/lacze_do_gnuplota.o obj/vector3d.o obj/solid.o obj/cuboid.o obj/prism6.o obj/drone.o obj/scene.o obj/matrix.o obj/ridge_hill.o obj/sharp_top_hill.o obj/table_land.o obj/sceneObject.o
	g++ -o ./${APP} obj/main.o obj/lacze_do_gnuplota.o obj/vector3d.o obj/solid.o obj/cuboid.o obj/prism6.o obj/drone.o obj/scene.o obj/matrix.o obj/ridge_hill.o obj/sharp_top_hill.o obj/table_land.o obj/sceneObject.o


ext: ./${APP}_rozszerzony
	rm -f core.* core; echo "2i 1+3.1i 2 ? / + ?" | ./${APP}_rozszerzony


obj/main.o: src/main.cpp
	g++  -Iinc -W -Wall -pedantic -c -o obj/main.o src/main.cpp

obj/lacze_do_gnuplota.o: src/lacze_do_gnuplota.cpp inc/lacze_do_gnuplota.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/vector3d.o: src/vector3d.cpp inc/vector.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/vector3d.o src/vector3d.cpp

obj/cuboid.o: src/cuboid.cpp inc/cuboid.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/cuboid.o src/cuboid.cpp

obj/solid.o: src/solid.cpp inc/solid.hh 
	g++ -Iinc -W -Wall -pedantic -c -o obj/solid.o src/solid.cpp

obj/prism6.o: src/prism6.cpp inc/prism6.hh
	g++ -Iinc -W -Wall -pedantic -c -o obj/prism6.o src/prism6.cpp

obj/drone.o: src/drone.cpp inc/drone.hh 
	g++ -Iinc -W -Wall -pedantic -c -o obj/drone.o src/drone.cpp

obj/scene.o: src/scene.cpp inc/scene.hh 
	g++ -Iinc -W -Wall -pedantic -c -o obj/scene.o src/scene.cpp

obj/matrix.o: src/matrix.cpp inc/matrix.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/matrix.o src/matrix.cpp

obj/ridge_hill.o: src/ridge_hill.cpp inc/ridge_hill.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/ridge_hill.o src/ridge_hill.cpp

obj/sharp_top_hill.o: src/sharp_top_hill.cpp inc/sharp_top_hill.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/sharp_top_hill.o src/sharp_top_hill.cpp

obj/table_land.o: src/table_land.cpp inc/table_land.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/table_land.o src/table_land.cpp

obj/sceneObject.o: src/sceneObject.cpp inc/sceneObject.hh
	g++  -Iinc -W -Wall -pedantic -c -o obj/sceneObject.o src/sceneObject.cpp

clean:
	rm -f obj/* ./${APP} core.* core

${TASKDIR}:
	mkdir -p ${TASKDIR}/bin.diablo ${TASKDIR}/bin.panamint

_TARGET_:
	if [ ! "${HOST}" = "diablo" ] && [ ! "${HOST}" = "panamint" ]; then exit 1; fi

export: _TARGET_ ./${APP}  ./${APP}_rozszerzony ${TASKDIR}
	mv ${APP} ${APP}_rozszerzony ${HOME}/edu/po/zad/z${TASKNO}/bin.${HOST}/

help:
	@echo
	@echo " make        - tworzenie i uruchomienie aplikacji"
	@echo " make ext    - tworzenie i uruchomienie aplikacji w wersji rozszerzonej"
	@echo " make clean  - usuniecie produktow kompilacji i konsolidacji"
	@echo " make help   - wyswietla niniejsza informacje"
	@echo