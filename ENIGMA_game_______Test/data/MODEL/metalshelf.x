xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 196;
 -36.75719;116.74833;-80.19201;,
 -29.18201;116.74833;-80.19201;,
 -29.18153;109.59162;-80.19201;,
 -36.75719;109.59096;-80.19201;,
 29.18201;116.74833;-80.19201;,
 29.18201;109.59096;-80.19201;,
 36.75719;116.74833;-80.19201;,
 36.75719;109.59096;-80.19201;,
 -29.18153;64.63873;-80.19201;,
 -36.75719;64.63900;-80.19201;,
 36.75719;64.63900;-80.19201;,
 29.18153;64.63900;-80.19201;,
 -29.18153;58.11801;-80.19201;,
 -36.75719;58.11769;-80.19201;,
 29.18201;58.11801;-80.19201;,
 36.75719;58.11769;-80.19201;,
 -29.18153;8.25396;-80.19201;,
 -36.75719;8.25396;-80.19201;,
 36.75719;8.25396;-80.19201;,
 29.18153;8.25396;-80.19201;,
 -29.18201;1.09674;-80.19201;,
 -36.75719;1.09674;-80.19201;,
 29.18201;1.09674;-80.19201;,
 36.75719;1.09674;-80.19201;,
 36.75719;116.74833;-80.19201;,
 36.75719;116.74833;-72.87595;,
 36.75719;109.59162;-72.87763;,
 36.75719;109.59096;-80.19201;,
 36.75719;116.74833;-5.01506;,
 36.75719;109.59096;-5.01671;,
 36.75719;116.74833;2.78886;,
 36.75719;109.59162;2.79052;,
 36.75719;116.74833;73.70795;,
 36.75719;109.59162;73.70795;,
 36.75719;116.74833;81.02400;,
 36.75719;109.59096;81.02400;,
 36.75719;64.63873;-72.87763;,
 36.75719;64.63900;-80.19201;,
 36.75719;64.63873;2.79052;,
 36.75719;64.63873;-5.01671;,
 36.75719;64.63900;81.02400;,
 36.75719;64.63900;73.70962;,
 36.75719;58.11769;-72.87595;,
 36.75719;58.11769;-80.19201;,
 36.75719;58.11801;-5.01671;,
 36.75719;58.11801;2.79052;,
 36.75719;58.11769;73.70795;,
 36.75719;58.11769;81.02400;,
 36.75719;8.25396;-72.87595;,
 36.75719;8.25396;-80.19201;,
 36.75719;8.25338;2.78886;,
 36.75719;8.25396;-5.01506;,
 36.75719;8.25396;81.02400;,
 36.75719;8.25396;73.70962;,
 36.75719;1.09674;-72.87595;,
 36.75719;1.09674;-80.19201;,
 36.75719;1.09674;-5.01506;,
 36.75719;1.09674;2.78886;,
 36.75719;1.09674;73.70795;,
 36.75719;1.09674;81.02400;,
 36.75719;116.74833;81.02400;,
 29.18201;116.74833;81.02400;,
 29.18201;109.59096;81.02400;,
 36.75719;109.59096;81.02400;,
 -29.18201;116.74833;81.02400;,
 -29.18153;109.59096;81.02400;,
 -36.75719;116.74833;81.02400;,
 -36.75719;109.59096;81.02400;,
 29.18153;64.63873;81.02400;,
 36.75719;64.63900;81.02400;,
 -36.75719;64.63900;81.02400;,
 -29.18153;64.63873;81.02400;,
 29.18153;58.11801;81.02400;,
 36.75719;58.11769;81.02400;,
 -29.18153;58.11801;81.02400;,
 -36.75719;58.11769;81.02400;,
 29.18153;8.25338;81.02400;,
 36.75719;8.25396;81.02400;,
 -36.75719;8.25396;81.02400;,
 -29.18153;8.25338;81.02400;,
 29.18201;1.09674;81.02400;,
 36.75719;1.09674;81.02400;,
 -29.18201;1.09674;81.02400;,
 -36.75719;1.09674;81.02400;,
 -36.75719;116.74833;81.02400;,
 -36.75719;116.74833;73.70795;,
 -36.75719;109.59162;73.70962;,
 -36.75719;109.59096;81.02400;,
 -36.75719;116.74833;2.78886;,
 -36.75719;109.59096;2.79052;,
 -36.75719;116.74833;-5.01506;,
 -36.75719;109.59162;-5.01671;,
 -36.75719;116.74833;-72.87595;,
 -36.75719;109.59096;-72.87763;,
 -36.75719;116.74833;-80.19201;,
 -36.75719;109.59096;-80.19201;,
 -36.75719;64.63900;73.70962;,
 -36.75719;64.63900;81.02400;,
 -36.75719;64.63900;-5.01671;,
 -36.75719;64.63873;2.78886;,
 -36.75719;64.63900;-80.19201;,
 -36.75719;64.63900;-72.87763;,
 -36.75719;58.11769;73.70795;,
 -36.75719;58.11769;81.02400;,
 -36.75719;58.11801;2.79052;,
 -36.75719;58.11769;-5.01506;,
 -36.75719;58.11769;-72.87763;,
 -36.75719;58.11769;-80.19201;,
 -36.75719;8.25396;73.70962;,
 -36.75719;8.25396;81.02400;,
 -36.75719;8.25338;-5.01671;,
 -36.75719;8.25338;2.79052;,
 -36.75719;8.25396;-80.19201;,
 -36.75719;8.25338;-72.87763;,
 -36.75719;1.09674;73.70795;,
 -36.75719;1.09674;81.02400;,
 -36.75719;1.09674;2.78886;,
 -36.75719;1.09674;-5.01506;,
 -36.75719;1.09674;-72.87595;,
 -36.75719;1.09674;-80.19201;,
 -29.18201;116.74833;81.02400;,
 -29.18201;116.74833;73.70795;,
 -36.75719;116.74833;73.70795;,
 29.18201;116.74833;81.02400;,
 29.18153;116.74833;73.70962;,
 36.75719;116.74833;73.70795;,
 -29.18201;116.74833;2.78886;,
 -36.75719;116.74833;2.78886;,
 29.18201;116.74833;2.78886;,
 36.75719;116.74833;2.78886;,
 -29.18153;116.74833;-5.01506;,
 -36.75719;116.74833;-5.01506;,
 29.18201;116.74833;-5.01506;,
 36.75719;116.74833;-5.01506;,
 -29.18201;116.74833;-72.87595;,
 -36.75719;116.74833;-72.87595;,
 29.00510;116.74833;-72.87595;,
 36.75719;116.74833;-72.87595;,
 -29.18201;116.74833;-80.19201;,
 -36.75719;116.74833;-80.19201;,
 29.18201;116.74833;-80.19201;,
 36.75719;116.74833;-80.19201;,
 -36.75719;1.09674;73.70795;,
 -29.18201;1.09674;73.70795;,
 -29.18201;1.09674;81.02400;,
 29.18201;1.09674;73.70795;,
 29.18201;1.09674;81.02400;,
 36.75719;1.09674;73.70795;,
 -36.75719;1.09674;2.78886;,
 -29.18153;1.09674;2.78886;,
 29.18153;1.09674;2.79052;,
 36.75719;1.09674;2.78886;,
 -36.75719;1.09674;-5.01506;,
 -29.18201;1.09674;-5.01506;,
 29.18201;1.09674;-5.01671;,
 36.75719;1.09674;-5.01506;,
 -36.75719;1.09674;-72.87595;,
 -29.18201;1.09674;-72.87595;,
 29.18201;1.09674;-72.87595;,
 36.75719;1.09674;-72.87595;,
 -36.75719;1.09674;-80.19201;,
 -29.18201;1.09674;-80.19201;,
 29.18201;1.09674;-80.19201;,
 36.75719;1.09674;-80.19201;,
 29.18153;64.63873;-72.87763;,
 -29.18153;64.63873;-72.87763;,
 -29.18153;109.59162;-72.87763;,
 29.00510;109.59162;-72.87763;,
 -29.18153;8.25338;-72.87763;,
 29.18153;8.25338;-72.87763;,
 -29.18153;58.11801;-72.87763;,
 29.18153;58.11801;-72.87763;,
 29.18153;64.63873;-5.01671;,
 29.18153;58.11801;-5.01671;,
 29.18153;64.63873;2.79052;,
 29.18153;64.63873;73.70962;,
 29.18153;58.11801;2.79052;,
 29.18153;58.11801;73.70962;,
 29.00510;109.59162;2.79052;,
 29.00510;109.59162;-5.01671;,
 -29.18153;109.59162;-5.01671;,
 -29.18153;109.59162;2.79052;,
 -29.18153;64.63873;-5.01671;,
 -29.18153;64.63873;2.79052;,
 -29.18153;58.11801;-5.01671;,
 -29.18153;58.11801;2.79052;,
 -29.18153;8.25338;-5.01671;,
 -29.18153;8.25338;2.79052;,
 -29.18153;109.59162;73.70962;,
 -29.18153;64.63873;73.70962;,
 -29.18153;58.11801;73.70962;,
 29.18153;109.59162;73.70962;,
 29.18153;8.25338;-5.01671;,
 29.18153;8.25338;2.79052;,
 -29.18153;8.25338;73.70962;,
 29.18153;8.25338;73.70962;;
 
 162;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;3,2,8,9;,
 4;5,7,10,11;,
 4;9,8,12,13;,
 4;8,11,14,12;,
 4;11,10,15,14;,
 4;13,12,16,17;,
 4;14,15,18,19;,
 4;17,16,20,21;,
 4;16,19,22,20;,
 4;19,18,23,22;,
 4;24,25,26,27;,
 4;25,28,29,26;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;27,26,36,37;,
 4;29,31,38,39;,
 4;33,35,40,41;,
 4;37,36,42,43;,
 4;36,39,44,42;,
 4;39,38,45,44;,
 4;38,41,46,45;,
 4;41,40,47,46;,
 4;43,42,48,49;,
 4;44,45,50,51;,
 4;46,47,52,53;,
 4;49,48,54,55;,
 4;48,51,56,54;,
 4;51,50,57,56;,
 4;50,53,58,57;,
 4;53,52,59,58;,
 4;60,61,62,63;,
 4;61,64,65,62;,
 4;64,66,67,65;,
 4;63,62,68,69;,
 4;65,67,70,71;,
 4;69,68,72,73;,
 4;68,71,74,72;,
 4;71,70,75,74;,
 4;73,72,76,77;,
 4;74,75,78,79;,
 4;77,76,80,81;,
 4;76,79,82,80;,
 4;79,78,83,82;,
 4;84,85,86,87;,
 4;85,88,89,86;,
 4;88,90,91,89;,
 4;90,92,93,91;,
 4;92,94,95,93;,
 4;87,86,96,97;,
 4;89,91,98,99;,
 4;93,95,100,101;,
 4;97,96,102,103;,
 4;96,99,104,102;,
 4;99,98,105,104;,
 4;98,101,106,105;,
 4;101,100,107,106;,
 4;103,102,108,109;,
 4;104,105,110,111;,
 4;106,107,112,113;,
 4;109,108,114,115;,
 4;108,111,116,114;,
 4;111,110,117,116;,
 4;110,113,118,117;,
 4;113,112,119,118;,
 4;84,120,121,122;,
 4;120,123,124,121;,
 4;123,34,125,124;,
 4;122,121,126,127;,
 4;121,124,128,126;,
 4;124,125,129,128;,
 4;127,126,130,131;,
 4;126,128,132,130;,
 4;128,129,133,132;,
 4;131,130,134,135;,
 4;130,132,136,134;,
 4;132,133,137,136;,
 4;135,134,138,139;,
 4;134,136,140,138;,
 4;136,137,141,140;,
 4;142,143,144,115;,
 4;143,145,146,144;,
 4;145,147,59,146;,
 4;148,149,143,142;,
 4;149,150,145,143;,
 4;150,151,147,145;,
 4;152,153,149,148;,
 4;153,154,150,149;,
 4;154,155,151,150;,
 4;156,157,153,152;,
 4;157,158,154,153;,
 4;158,159,155,154;,
 4;160,161,157,156;,
 4;161,162,158,157;,
 4;162,163,159,158;,
 4;164,11,8,165;,
 4;2,166,165,8;,
 4;36,26,167,164;,
 4;167,5,11,164;,
 4;166,93,101,165;,
 4;19,16,168,169;,
 4;12,170,168,16;,
 4;170,106,113,168;,
 4;19,169,171,14;,
 4;42,171,169,48;,
 4;14,171,170,12;,
 4;36,164,172,39;,
 4;171,42,44,173;,
 4;38,174,175,41;,
 4;176,45,46,177;,
 4;178,179,172,174;,
 4;179,29,39,172;,
 4;31,178,174,38;,
 4;29,179,167,26;,
 4;166,2,5,167;,
 4;93,166,180,91;,
 4;179,180,166,167;,
 4;181,180,179,178;,
 4;98,182,165,101;,
 4;180,181,183,182;,
 4;91,180,182,98;,
 4;181,89,99,183;,
 4;171,173,184,170;,
 4;165,182,172,164;,
 4;182,183,174,172;,
 4;185,184,173,176;,
 4;110,186,168,113;,
 4;105,184,186,110;,
 4;184,105,106,170;,
 4;184,185,187,186;,
 4;86,188,189,96;,
 4;188,65,71,189;,
 4;183,99,96,189;,
 4;183,189,175,174;,
 4;189,71,68,175;,
 4;185,104,111,187;,
 4;176,177,190,185;,
 4;181,178,191,188;,
 4;89,181,188,86;,
 4;178,31,33,191;,
 4;33,41,175,191;,
 4;62,191,175,68;,
 4;65,188,191,62;,
 4;104,185,190,102;,
 4;74,190,177,72;,
 4;48,169,192,51;,
 4;168,186,192,169;,
 4;44,51,192,173;,
 4;45,176,193,50;,
 4;176,173,192,193;,
 4;186,187,193,192;,
 4;187,111,108,194;,
 4;102,190,194,108;,
 4;190,74,79,194;,
 4;194,79,76,195;,
 4;50,193,195,53;,
 4;195,193,187,194;,
 4;177,46,53,195;,
 4;72,177,195,76;;
 
 MeshMaterialList {
  1;
  162;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.545600;0.545600;0.545600;1.000000;;
   5.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  56;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000011;1.000000;0.000006;,
  -0.000001;1.000000;0.000006;,
  0.000000;1.000000;0.000026;,
  -0.000025;1.000000;0.000026;,
  -1.000000;0.000005;-0.000033;,
  -0.000006;1.000000;-0.000001;,
  -0.000007;-1.000000;0.000001;,
  -0.000007;-1.000000;-0.000001;,
  -0.999992;-0.003925;0.000000;,
  0.000015;-1.000000;0.000002;,
  0.000015;-1.000000;0.000002;,
  0.000012;1.000000;0.000000;,
  0.000007;-1.000000;-0.000001;,
  0.000014;-1.000000;-0.000000;,
  0.000000;-1.000000;-0.000030;,
  0.000109;-0.000017;1.000000;,
  -0.000025;1.000000;0.000000;,
  0.000013;1.000000;-0.000001;,
  -0.000013;1.000000;-0.000001;,
  -0.000002;1.000000;0.000019;,
  -0.999925;-0.001957;-0.012090;,
  0.000000;1.000000;0.000079;,
  -0.000222;0.000000;1.000000;,
  -0.000021;-1.000000;0.000002;,
  -0.000018;1.000000;-0.000002;,
  -0.000021;-1.000000;-0.000002;,
  -0.000043;-1.000000;-0.000005;,
  -0.000014;-1.000000;-0.000002;,
  -0.000016;-1.000000;0.000013;,
  0.000013;-1.000000;0.000017;,
  -0.000006;-1.000000;0.000045;,
  0.000044;-1.000000;0.000005;,
  0.000036;1.000000;0.000000;,
  -0.000109;-0.000018;1.000000;,
  0.000006;1.000000;-0.000001;,
  -0.000109;0.000017;-1.000000;,
  0.000041;-1.000000;-0.000000;,
  0.000018;1.000000;-0.000002;,
  0.000015;-1.000000;-0.000028;,
  0.000044;-1.000000;0.000005;,
  -0.000110;-0.000019;-1.000000;,
  -1.000000;0.000005;0.000033;,
  0.000000;-1.000000;-0.000090;,
  0.000021;-1.000000;-0.000002;,
  -0.000076;1.000000;0.000000;,
  0.000109;-0.000017;-1.000000;,
  0.000038;1.000000;-0.000004;,
  0.000110;-0.000017;-1.000000;,
  -0.000038;1.000000;-0.000004;,
  -0.000110;-0.000017;-1.000000;;
  162;
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;7,25,25,6;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;26,26,26,26;,
  4;2,2,2,2;,
  4;27,27,8,9;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;10,10,10,10;,
  4;28,28,28,28;,
  4;5,12,19,5;,
  4;4,7,4,4;,
  4;12,29,29,12;,
  4;30,11,11,30;,
  4;13,31,31,13;,
  4;14,14,14,14;,
  4;0,0,0,0;,
  4;2,2,2,2;,
  4;32,33,34,32;,
  4;35,36,36,34;,
  4;37,35,15,37;,
  4;33,15,35,34;,
  4;16,15,33,5;,
  4;38,17,6,38;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;39,39,39,39;,
  4;12,12,19,19;,
  4;6,17,4,7;,
  4;17,40,11,4;,
  4;18,19,12,13;,
  4;4,4,8,4;,
  4;41,41,41,41;,
  4;19,42,42,19;,
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;40,43,43,40;,
  4;40,40,11,11;,
  4;40,4,4,11;,
  4;2,2,2,2;,
  4;13,13,18,18;,
  4;16,5,20,44;,
  4;45,16,44,45;,
  4;5,5,5,20;,
  4;46,46,46,46;,
  4;47,47,47,47;,
  4;48,44,20,48;,
  4;49,18,18,49;,
  4;5,18,13,5;,
  4;50,9,22,50;,
  4;8,4,22,9;,
  4;51,51,51,51;,
  4;21,21,21,21;,
  4;3,3,3,3;,
  4;4,23,24,22;,
  4;23,52,52,23;,
  4;53,53,53,53;,
  4;1,1,1,1;,
  4;23,4,4,24;,
  4;54,24,24,54;,
  4;24,24,23,23;,
  4;55,55,55,55;,
  4;3,3,3,3;;
 }
 MeshTextureCoords {
  196;
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.200000;,
  0.000000;0.200000;,
  0.666670;0.000000;,
  0.666670;0.200000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.333330;0.400000;,
  0.000000;0.400000;,
  1.000000;0.400000;,
  0.666670;0.400000;,
  0.333330;0.600000;,
  0.000000;0.600000;,
  0.666670;0.600000;,
  1.000000;0.600000;,
  0.333330;0.800000;,
  0.000000;0.800000;,
  1.000000;0.800000;,
  0.666670;0.800000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.200000;0.000000;,
  0.200000;0.200000;,
  0.000000;0.200000;,
  0.400000;0.000000;,
  0.400000;0.200000;,
  0.600000;0.000000;,
  0.600000;0.200000;,
  0.800000;0.000000;,
  0.800000;0.200000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.200000;0.400000;,
  0.000000;0.400000;,
  0.600000;0.400000;,
  0.400000;0.400000;,
  1.000000;0.400000;,
  0.800000;0.400000;,
  0.200000;0.600000;,
  0.000000;0.600000;,
  0.400000;0.600000;,
  0.600000;0.600000;,
  0.800000;0.600000;,
  1.000000;0.600000;,
  0.200000;0.800000;,
  0.000000;0.800000;,
  0.600000;0.800000;,
  0.400000;0.800000;,
  1.000000;0.800000;,
  0.800000;0.800000;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.400000;1.000000;,
  0.600000;1.000000;,
  0.800000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;0.200000;,
  0.000000;0.200000;,
  0.666670;0.000000;,
  0.666670;0.200000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.333330;0.400000;,
  0.000000;0.400000;,
  1.000000;0.400000;,
  0.666670;0.400000;,
  0.333330;0.600000;,
  0.000000;0.600000;,
  0.666670;0.600000;,
  1.000000;0.600000;,
  0.333330;0.800000;,
  0.000000;0.800000;,
  1.000000;0.800000;,
  0.666670;0.800000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.200000;0.000000;,
  0.200000;0.200000;,
  0.000000;0.200000;,
  0.400000;0.000000;,
  0.400000;0.200000;,
  0.600000;0.000000;,
  0.600000;0.200000;,
  0.800000;0.000000;,
  0.800000;0.200000;,
  1.000000;0.000000;,
  1.000000;0.200000;,
  0.200000;0.400000;,
  0.000000;0.400000;,
  0.600000;0.400000;,
  0.400000;0.400000;,
  1.000000;0.400000;,
  0.800000;0.400000;,
  0.200000;0.600000;,
  0.000000;0.600000;,
  0.400000;0.600000;,
  0.600000;0.600000;,
  0.800000;0.600000;,
  1.000000;0.600000;,
  0.200000;0.800000;,
  0.000000;0.800000;,
  0.600000;0.800000;,
  0.400000;0.800000;,
  1.000000;0.800000;,
  0.800000;0.800000;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.400000;1.000000;,
  0.600000;1.000000;,
  0.800000;1.000000;,
  1.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;0.200000;,
  0.000000;0.200000;,
  0.666670;0.000000;,
  0.666670;0.200000;,
  1.000000;0.200000;,
  0.333330;0.400000;,
  0.000000;0.400000;,
  0.666670;0.400000;,
  1.000000;0.400000;,
  0.333330;0.600000;,
  0.000000;0.600000;,
  0.666670;0.600000;,
  1.000000;0.600000;,
  0.333330;0.800000;,
  0.000000;0.800000;,
  0.666670;0.800000;,
  1.000000;0.800000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.800000;,
  0.333330;0.800000;,
  0.333330;1.000000;,
  0.666670;0.800000;,
  0.666670;1.000000;,
  1.000000;0.800000;,
  0.000000;0.600000;,
  0.333330;0.600000;,
  0.666670;0.600000;,
  1.000000;0.600000;,
  0.000000;0.400000;,
  0.333330;0.400000;,
  0.666670;0.400000;,
  1.000000;0.400000;,
  0.000000;0.200000;,
  0.333330;0.200000;,
  0.666670;0.200000;,
  1.000000;0.200000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
