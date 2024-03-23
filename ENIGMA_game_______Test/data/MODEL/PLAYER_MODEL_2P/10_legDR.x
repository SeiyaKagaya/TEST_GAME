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
 82;
 0.03952;0.24533;0.58654;,
 1.82688;0.24533;-1.22779;,
 0.03952;0.24533;-1.97930;,
 2.56723;0.24533;0.58654;,
 1.82688;0.24533;2.40086;,
 0.03952;0.24533;3.15237;,
 -1.74784;0.24533;2.40086;,
 -2.48820;0.24533;0.58654;,
 -1.74784;0.24533;-1.22779;,
 1.99788;0.10261;-1.40136;,
 0.03952;0.10261;-2.22476;,
 2.80906;0.10261;0.58654;,
 1.99788;0.10261;2.57443;,
 0.03952;0.10261;3.39783;,
 -1.91885;0.10261;2.57443;,
 -2.73003;0.10261;0.58654;,
 -1.91885;0.10261;-1.40136;,
 2.14286;-0.30368;-1.54850;,
 0.03952;-0.30368;-2.43287;,
 3.01409;-0.30368;0.58654;,
 2.14286;-0.30368;2.72157;,
 0.03952;-0.30368;3.60594;,
 -2.06383;-0.30368;2.72157;,
 -2.93506;-0.30368;0.58654;,
 -2.06383;-0.30368;-1.54850;,
 2.23971;-0.91180;-1.64682;,
 0.03952;-0.91180;-2.57193;,
 3.15107;-0.91180;0.58654;,
 2.23971;-0.91180;2.81989;,
 0.03952;-0.91180;3.74500;,
 -2.16068;-0.91180;2.81989;,
 -3.07203;-0.91180;0.58654;,
 -2.16068;-0.91180;-1.64682;,
 2.27374;-1.62910;-1.68136;,
 0.03952;-1.62910;-2.62074;,
 3.19917;-1.62910;0.58654;,
 2.27374;-1.62910;2.85443;,
 0.03952;-1.62910;3.79382;,
 -2.19470;-1.62910;2.85443;,
 -3.12014;-1.62910;0.58654;,
 -2.19470;-1.62910;-1.68136;,
 2.27374;-16.62460;-1.68136;,
 0.03952;-16.62460;-2.62074;,
 3.19917;-16.62460;0.58654;,
 2.27374;-16.62460;2.85443;,
 0.03952;-16.62460;3.79382;,
 -2.19470;-16.62460;2.85443;,
 -3.12014;-16.62460;0.58654;,
 -2.19470;-16.62460;-1.68136;,
 2.23971;-17.34194;-1.64682;,
 0.03952;-17.34194;-2.57193;,
 3.15107;-17.34194;0.58654;,
 2.23971;-17.34194;2.81989;,
 0.03952;-17.34194;3.74500;,
 -2.16068;-17.34194;2.81989;,
 -3.07203;-17.34194;0.58654;,
 -2.16068;-17.34194;-1.64682;,
 2.14286;-17.95003;-1.54850;,
 0.03952;-17.95003;-2.43287;,
 3.01409;-17.95003;0.58654;,
 2.14286;-17.95003;2.72157;,
 0.03952;-17.95003;3.60594;,
 -2.06383;-17.95003;2.72157;,
 -2.93506;-17.95003;0.58654;,
 -2.06383;-17.95003;-1.54850;,
 1.99788;-18.35637;-1.40136;,
 0.03952;-18.35637;-2.22476;,
 2.80906;-18.35637;0.58654;,
 1.99788;-18.35637;2.57443;,
 0.03952;-18.35637;3.39783;,
 -1.91885;-18.35637;2.57443;,
 -2.73003;-18.35637;0.58654;,
 -1.91885;-18.35637;-1.40136;,
 1.82688;-18.49902;-1.22779;,
 0.03952;-18.49902;-1.97930;,
 2.56723;-18.49902;0.58654;,
 1.82688;-18.49902;2.40086;,
 0.03952;-18.49902;3.15237;,
 -1.74784;-18.49902;2.40086;,
 -2.48820;-18.49902;0.58654;,
 -1.74784;-18.49902;-1.22779;,
 0.03952;-18.49902;0.58654;;
 
 88;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,2,8;,
 4;2,1,9,10;,
 4;1,3,11,9;,
 4;3,4,12,11;,
 4;4,5,13,12;,
 4;5,6,14,13;,
 4;6,7,15,14;,
 4;7,8,16,15;,
 4;8,2,10,16;,
 4;10,9,17,18;,
 4;9,11,19,17;,
 4;11,12,20,19;,
 4;12,13,21,20;,
 4;13,14,22,21;,
 4;14,15,23,22;,
 4;15,16,24,23;,
 4;16,10,18,24;,
 4;18,17,25,26;,
 4;17,19,27,25;,
 4;19,20,28,27;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,18,26,32;,
 4;26,25,33,34;,
 4;25,27,35,33;,
 4;27,28,36,35;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,26,34,40;,
 4;34,33,41,42;,
 4;33,35,43,41;,
 4;35,36,44,43;,
 4;36,37,45,44;,
 4;37,38,46,45;,
 4;38,39,47,46;,
 4;39,40,48,47;,
 4;40,34,42,48;,
 4;42,41,49,50;,
 4;41,43,51,49;,
 4;43,44,52,51;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,42,50,56;,
 4;50,49,57,58;,
 4;49,51,59,57;,
 4;51,52,60,59;,
 4;52,53,61,60;,
 4;53,54,62,61;,
 4;54,55,63,62;,
 4;55,56,64,63;,
 4;56,50,58,64;,
 4;58,57,65,66;,
 4;57,59,67,65;,
 4;59,60,68,67;,
 4;60,61,69,68;,
 4;61,62,70,69;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;64,58,66,72;,
 4;66,65,73,74;,
 4;65,67,75,73;,
 4;67,68,76,75;,
 4;68,69,77,76;,
 4;69,70,78,77;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;72,66,74,80;,
 3;74,73,81;,
 3;73,75,81;,
 3;75,76,81;,
 3;76,77,81;,
 3;77,78,81;,
 3;78,79,81;,
 3;79,80,81;,
 3;80,74,81;;
 
 MeshMaterialList {
  8;
  88;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.752800;0.602400;0.445600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.718431;0.718431;0.718431;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.771765;0.771765;0.771765;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.163200;0.401600;0.586400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.476800;0.075200;0.060000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Downloads\\Welcome2P.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Downloads\\skirt001.png";
   }
  }
  Material {
   0.690400;0.636800;0.125600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  82;
  0.000000;1.000000;0.000000;,
  0.000000;0.966292;-0.257448;,
  0.184434;0.965861;-0.181925;,
  0.260660;0.965431;0.000000;,
  0.184434;0.965861;0.181925;,
  0.000000;0.966292;0.257448;,
  -0.184431;0.965862;0.181924;,
  -0.260655;0.965432;0.000000;,
  -0.184431;0.965862;-0.181924;,
  0.000001;0.692654;-0.721270;,
  0.514765;0.690246;-0.508506;,
  0.725844;0.687859;0.000001;,
  0.514764;0.690246;0.508506;,
  0.000001;0.692654;0.721270;,
  -0.514762;0.690248;0.508505;,
  -0.725841;0.687863;0.000001;,
  -0.514762;0.690248;-0.508505;,
  0.000001;0.342743;-0.939429;,
  0.668513;0.340521;-0.661162;,
  0.941028;0.338329;0.000001;,
  0.668513;0.340521;0.661163;,
  0.000001;0.342743;0.939429;,
  -0.668513;0.340520;0.661163;,
  -0.941029;0.338325;0.000001;,
  -0.668513;0.340520;-0.661163;,
  0.000001;0.145990;-0.989286;,
  0.703368;0.144928;-0.695894;,
  0.989595;0.143881;0.000001;,
  0.703368;0.144929;0.695894;,
  0.000001;0.145993;0.989286;,
  -0.703368;0.144927;0.695894;,
  -0.989596;0.143877;0.000001;,
  -0.703369;0.144925;-0.695894;,
  0.000000;0.033983;-0.999422;,
  0.710436;0.033733;-0.702953;,
  0.999439;0.033486;0.000001;,
  0.710437;0.033735;0.702952;,
  0.000000;0.033986;0.999422;,
  -0.710436;0.033734;0.702953;,
  -0.999439;0.033486;0.000001;,
  -0.710435;0.033732;-0.702954;,
  0.000000;-0.033981;-0.999422;,
  0.710436;-0.033731;-0.702953;,
  0.999439;-0.033484;0.000001;,
  0.710437;-0.033733;0.702952;,
  0.000000;-0.033985;0.999422;,
  -0.710436;-0.033732;0.702953;,
  -0.999439;-0.033484;0.000001;,
  -0.710435;-0.033730;-0.702954;,
  0.000001;-0.145993;-0.989286;,
  0.703368;-0.144931;-0.695894;,
  0.989595;-0.143884;0.000001;,
  0.703368;-0.144933;0.695894;,
  0.000001;-0.145997;0.989285;,
  -0.703368;-0.144931;0.695894;,
  -0.989595;-0.143880;0.000001;,
  -0.703368;-0.144929;-0.695894;,
  0.000001;-0.342724;-0.939436;,
  0.668518;-0.340502;-0.661167;,
  0.941035;-0.338310;0.000001;,
  0.668517;-0.340502;0.661168;,
  0.000001;-0.342724;0.939436;,
  -0.668518;-0.340501;0.661168;,
  -0.941036;-0.338306;0.000001;,
  -0.668518;-0.340501;-0.661168;,
  0.000001;-0.692717;-0.721209;,
  0.514721;-0.690310;-0.508463;,
  0.725783;-0.687923;0.000001;,
  0.514721;-0.690309;0.508464;,
  0.000001;-0.692717;0.721210;,
  -0.514718;-0.690312;0.508463;,
  -0.725780;-0.687927;0.000001;,
  -0.514719;-0.690312;-0.508462;,
  0.000000;-0.966319;-0.257349;,
  0.184363;-0.965888;-0.181855;,
  0.260559;-0.965458;0.000000;,
  0.184363;-0.965888;0.181855;,
  0.000000;-0.966319;0.257349;,
  -0.184360;-0.965889;0.181854;,
  -0.260554;-0.965459;0.000000;,
  -0.184360;-0.965889;-0.181853;,
  0.000000;-1.000000;-0.000000;;
  88;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  4;49,50,58,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,49,57,64;,
  4;57,58,66,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,57,65,72;,
  4;65,66,74,73;,
  4;66,67,75,74;,
  4;67,68,76,75;,
  4;68,69,77,76;,
  4;69,70,78,77;,
  4;70,71,79,78;,
  4;71,72,80,79;,
  4;72,65,73,80;,
  3;73,74,81;,
  3;74,75,81;,
  3;75,76,81;,
  3;76,77,81;,
  3;77,78,81;,
  3;78,79,81;,
  3;79,80,81;,
  3;80,73,81;;
 }
 MeshTextureCoords {
  82;
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