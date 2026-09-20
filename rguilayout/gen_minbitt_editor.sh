#!/bin/bash

if [ "$1" = "" ]
then
  echo Error:
  echo "  Usage: $0 <output file name>"
  exit
fi

OUTPUT_FILE=$1

# Note the meson script has to run first before this one
#cd src
# ultra jank using of meson build artifacts
#make RAYLIB_LIB_PATH=../../buildDir/subprojects/raylib RAYLIB_INCLUDE_PATH=../../buildDir/subprojects/raylib/__CMake_build/raylib/include/
#cd ..
#./src/rguilayout \
 #TODO: wait for rguilayout pull to uncomment all above lines
./rguilayout-patched \
  --input minbitt_editor_v1.rgl \
  --output $OUTPUT_FILE \
  --template template.h \
  --name minbitt_editor \
  --version 1.0.0 \
  --company "Spitball Engineering" \
  --description "simple tool to tune face tracking data" \
  --rectangles \
  --texts \
  --buttons

# moving const text up
ed -s $OUTPUT_FILE <<__END__
/Const text$/,/Draw controls$/-m/Global Variables Definition/+
wq
__END__

#removing some const char TODO: might not need
sed -i 's/const char \*BlendEyeXValLabelText/char BlendEyeXValLabelText\[\]/' $OUTPUT_FILE
sed -i 's/const char \*BlendEyeYValLabelText/char BlendEyeYValLabelText\[\]/' $OUTPUT_FILE
sed -E -i 's|const char \*(.*) = (.*) SLIDER: (.*)|char \1\[\] = \2 SLIDER: \3|' $OUTPUT_FILE # making all slider text non const

#changing generated btn signiture to extern
sed -E -i 's|^static void (.*;)|extern void \1|g' $OUTPUT_FILE
#deleting generated btn functions
sed -i '/static void .*\(\)/,/\}/d' $OUTPUT_FILE

# -- renaming all layoutRecs --
# Source - https://stackoverflow.com/a/35927896

#prints out regex capture groups and pipes it into while loop
sed -n 's/state.layoutRecs\[\(.*\)] = (Rectangle).*: \(.*\)/\1 \2/p' $OUTPUT_FILE | \
while read -r num var; do
  # creates new sed string to find and replace all layoutRecs[..] with paired variable name
  str=s/layoutRecs\\[$num\\]/${var}Rec/g
  sed -i "${str}" $OUTPUT_FILE
done

# deletes Rectangels layoutRecs[31] in struct
sed -i '/Rectangle layoutRecs\[.*\];/d' $OUTPUT_FILE

# moving all Recs into struct
ed -s $OUTPUT_FILE <<__END__
/Init controls rectangles$/,/Custom variables initialization$/-t/Define rectangles$/
wq
__END__
# changing all state.xxxRec = (Rectange){...};   to   Rectangle xxx;
sed -i '/Define rectangles/,/Custom state variables/s/state.\(.*Rec\) =.*/Rectangle \1;/' $OUTPUT_FILE

#deleting dummy rec draw calls
sed -i '/GuiDummyRec/d' $OUTPUT_FILE
