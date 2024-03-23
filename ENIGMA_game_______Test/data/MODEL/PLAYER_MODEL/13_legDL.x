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
 -0.00528;0.24533;0.58654;,
 -0.00528;0.24533;-1.97930;,
 -1.79264;0.24533;-1.22779;,
 -2.53299;0.24533;0.58654;,
 -1.79264;0.24533;2.40086;,
 -0.00528;0.24533;3.15237;,
 1.78208;0.24533;2.40086;,
 2.52244;0.24533;0.58654;,
 1.78208;0.24533;-1.22779;,
 -0.00528;0.10261;-2.22476;,
 -1.96364;0.10261;-1.40136;,
 -2.77482;0.10261;0.58654;,
 -1.96364;0.10261;2.57443;,
 -0.00528;0.10261;3.39783;,
 1.95309;0.10261;2.57443;,
 2.76427;0.10261;0.58654;,
 1.95309;0.10261;-1.40136;,
 -0.00528;-0.30368;-2.43287;,
 -2.10862;-0.30368;-1.54850;,
 -2.97985;-0.30368;0.58654;,
 -2.10862;-0.30368;2.72157;,
 -0.00528;-0.30368;3.60594;,
 2.09807;-0.30368;2.72157;,
 2.96930;-0.30368;0.58654;,
 2.09807;-0.30368;-1.54850;,
 -0.00528;-0.91180;-2.57193;,
 -2.20547;-0.91180;-1.64682;,
 -3.11683;-0.91180;0.58654;,
 -2.20547;-0.91180;2.81990;,
 -0.00528;-0.91180;3.74500;,
 2.19492;-0.91180;2.81990;,
 3.10627;-0.91180;0.58654;,
 2.19492;-0.91180;-1.64682;,
 -0.00528;-1.62910;-2.62074;,
 -2.23950;-1.62910;-1.68136;,
 -3.16493;-1.62910;0.58654;,
 -2.23950;-1.62910;2.85443;,
 -0.00528;-1.62910;3.79382;,
 2.22894;-1.62910;2.85443;,
 3.15438;-1.62910;0.58654;,
 2.22894;-1.62910;-1.68136;,
 -0.00528;-16.62460;-2.62074;,
 -2.23950;-16.62460;-1.68136;,
 -3.16493;-16.62460;0.58654;,
 -2.23950;-16.62460;2.85443;,
 -0.00528;-16.62460;3.79382;,
 2.22894;-16.62460;2.85443;,
 3.15438;-16.62460;0.58654;,
 2.22894;-16.62460;-1.68136;,
 -0.00528;-17.34195;-2.57193;,
 -2.20547;-17.34195;-1.64682;,
 -3.11683;-17.34195;0.58654;,
 -2.20547;-17.34195;2.81990;,
 -0.00528;-17.34195;3.74500;,
 2.19492;-17.34195;2.81990;,
 3.10627;-17.34195;0.58654;,
 2.19492;-17.34195;-1.64682;,
 -0.00528;-17.95003;-2.43287;,
 -2.10862;-17.95003;-1.54850;,
 -2.97985;-17.95003;0.58654;,
 -2.10862;-17.95003;2.72157;,
 -0.00528;-17.95003;3.60594;,
 2.09807;-17.95003;2.72157;,
 2.96930;-17.95003;0.58654;,
 2.09807;-17.95003;-1.54850;,
 -0.00528;-18.35637;-2.22476;,
 -1.96364;-18.35637;-1.40136;,
 -2.77482;-18.35637;0.58654;,
 -1.96364;-18.35637;2.57443;,
 -0.00528;-18.35637;3.39783;,
 1.95309;-18.35637;2.57443;,
 2.76427;-18.35637;0.58654;,
 1.95309;-18.35637;-1.40136;,
 -0.00528;-18.49903;-1.97930;,
 -1.79264;-18.49903;-1.22779;,
 -2.53299;-18.49903;0.58654;,
 -1.79264;-18.49903;2.40086;,
 -0.00528;-18.49903;3.15237;,
 1.78208;-18.49903;2.40086;,
 2.52244;-18.49903;0.58654;,
 1.78208;-18.49903;-1.22779;,
 -0.00528;-18.49903;0.58654;;
 
 88;
 3;0,1,2;,
 3;0,2,3;,
 3;0,3,4;,
 3;0,4,5;,
 3;0,5,6;,
 3;0,6,7;,
 3;0,7,8;,
 3;0,8,1;,
 4;1,9,10,2;,
 4;2,10,11,3;,
 4;3,11,12,4;,
 4;4,12,13,5;,
 4;5,13,14,6;,
 4;6,14,15,7;,
 4;7,15,16,8;,
 4;8,16,9,1;,
 4;9,17,18,10;,
 4;10,18,19,11;,
 4;11,19,20,12;,
 4;12,20,21,13;,
 4;13,21,22,14;,
 4;14,22,23,15;,
 4;15,23,24,16;,
 4;16,24,17,9;,
 4;17,25,26,18;,
 4;18,26,27,19;,
 4;19,27,28,20;,
 4;20,28,29,21;,
 4;21,29,30,22;,
 4;22,30,31,23;,
 4;23,31,32,24;,
 4;24,32,25,17;,
 4;25,33,34,26;,
 4;26,34,35,27;,
 4;27,35,36,28;,
 4;28,36,37,29;,
 4;29,37,38,30;,
 4;30,38,39,31;,
 4;31,39,40,32;,
 4;32,40,33,25;,
 4;33,41,42,34;,
 4;34,42,43,35;,
 4;35,43,44,36;,
 4;36,44,45,37;,
 4;37,45,46,38;,
 4;38,46,47,39;,
 4;39,47,48,40;,
 4;40,48,41,33;,
 4;41,49,50,42;,
 4;42,50,51,43;,
 4;43,51,52,44;,
 4;44,52,53,45;,
 4;45,53,54,46;,
 4;46,54,55,47;,
 4;47,55,56,48;,
 4;48,56,49,41;,
 4;49,57,58,50;,
 4;50,58,59,51;,
 4;51,59,60,52;,
 4;52,60,61,53;,
 4;53,61,62,54;,
 4;54,62,63,55;,
 4;55,63,64,56;,
 4;56,64,57,49;,
 4;57,65,66,58;,
 4;58,66,67,59;,
 4;59,67,68,60;,
 4;60,68,69,61;,
 4;61,69,70,62;,
 4;62,70,71,63;,
 4;63,71,72,64;,
 4;64,72,65,57;,
 4;65,73,74,66;,
 4;66,74,75,67;,
 4;67,75,76,68;,
 4;68,76,77,69;,
 4;69,77,78,70;,
 4;70,78,79,71;,
 4;71,79,80,72;,
 4;72,80,73,65;,
 3;73,81,74;,
 3;74,81,75;,
 3;75,81,76;,
 3;76,81,77;,
 3;77,81,78;,
 3;78,81,79;,
 3;79,81,80;,
 3;80,81,73;;
 
 MeshMaterialList {
  7;
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
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.178824;0.178824;0.178824;1.000000;;
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
   0.476863;0.075294;0.059608;1.000000;;
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
    "C:\\Users\\student\\Downloads\\Welcome.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Downloads\\skirt.png";
   }
  }
 }
 MeshNormals {
  82;
  0.000000;1.000000;0.000000;,
  -0.000000;0.966295;-0.257436;,
  -0.184425;0.965864;-0.181917;,
  -0.260648;0.965434;0.000000;,
  -0.184426;0.965864;0.181918;,
  -0.000000;0.966295;0.257438;,
  0.184425;0.965864;0.181917;,
  0.260646;0.965434;0.000000;,
  0.184424;0.965864;-0.181916;,
  -0.000000;0.692660;-0.721264;,
  -0.514760;0.690252;-0.508502;,
  -0.725838;0.687866;0.000000;,
  -0.514760;0.690252;0.508502;,
  -0.000000;0.692659;0.721265;,
  0.514759;0.690253;0.508502;,
  0.725837;0.687866;0.000000;,
  0.514759;0.690253;-0.508501;,
  -0.000000;0.342739;-0.939431;,
  -0.668513;0.340518;-0.661164;,
  -0.941029;0.338325;0.000000;,
  -0.668513;0.340517;0.661164;,
  -0.000000;0.342738;0.939431;,
  0.668514;0.340516;0.661164;,
  0.941030;0.338323;0.000000;,
  0.668514;0.340517;-0.661164;,
  0.000000;0.145994;-0.989285;,
  -0.703368;0.144930;-0.695894;,
  -0.989595;0.143881;0.000000;,
  -0.703368;0.144929;0.695895;,
  0.000000;0.145992;0.989286;,
  0.703368;0.144928;0.695895;,
  0.989595;0.143880;0.000000;,
  0.703368;0.144929;-0.695894;,
  0.000000;0.033985;-0.999422;,
  -0.710436;0.033734;-0.702953;,
  -0.999439;0.033487;0.000000;,
  -0.710436;0.033735;0.702953;,
  0.000000;0.033986;0.999422;,
  0.710436;0.033734;0.702953;,
  0.999439;0.033486;0.000000;,
  0.710436;0.033734;-0.702953;,
  0.000000;-0.033983;-0.999422;,
  -0.710436;-0.033732;-0.702953;,
  -0.999439;-0.033485;0.000000;,
  -0.710436;-0.033733;0.702953;,
  0.000000;-0.033983;0.999422;,
  0.710436;-0.033732;0.702953;,
  0.999439;-0.033484;0.000000;,
  0.710436;-0.033731;-0.702953;,
  0.000000;-0.145998;-0.989285;,
  -0.703367;-0.144934;-0.695894;,
  -0.989594;-0.143885;0.000000;,
  -0.703367;-0.144932;0.695895;,
  0.000000;-0.145995;0.989285;,
  0.703367;-0.144932;0.695895;,
  0.989595;-0.143883;0.000000;,
  0.703368;-0.144933;-0.695894;,
  -0.000000;-0.342721;-0.939437;,
  -0.668518;-0.340500;-0.661168;,
  -0.941036;-0.338307;0.000000;,
  -0.668518;-0.340499;0.661169;,
  -0.000000;-0.342721;0.939437;,
  0.668518;-0.340499;0.661169;,
  0.941036;-0.338305;0.000000;,
  0.668518;-0.340499;-0.661168;,
  -0.000000;-0.692713;-0.721213;,
  -0.514723;-0.690306;-0.508466;,
  -0.725786;-0.687920;0.000000;,
  -0.514723;-0.690306;0.508466;,
  -0.000000;-0.692713;0.721214;,
  0.514723;-0.690306;0.508466;,
  0.725786;-0.687920;0.000000;,
  0.514723;-0.690307;-0.508465;,
  -0.000000;-0.966318;-0.257349;,
  -0.184363;-0.965888;-0.181855;,
  -0.260560;-0.965458;0.000000;,
  -0.184364;-0.965887;0.181857;,
  -0.000000;-0.966318;0.257351;,
  0.184363;-0.965888;0.181856;,
  0.260559;-0.965458;0.000000;,
  0.184362;-0.965888;-0.181855;,
  0.000000;-1.000000;-0.000000;;
  88;
  3;0,1,2;,
  3;0,2,3;,
  3;0,3,4;,
  3;0,4,5;,
  3;0,5,6;,
  3;0,6,7;,
  3;0,7,8;,
  3;0,8,1;,
  4;1,9,10,2;,
  4;2,10,11,3;,
  4;3,11,12,4;,
  4;4,12,13,5;,
  4;5,13,14,6;,
  4;6,14,15,7;,
  4;7,15,16,8;,
  4;8,16,9,1;,
  4;9,17,18,10;,
  4;10,18,19,11;,
  4;11,19,20,12;,
  4;12,20,21,13;,
  4;13,21,22,14;,
  4;14,22,23,15;,
  4;15,23,24,16;,
  4;16,24,17,9;,
  4;17,25,26,18;,
  4;18,26,27,19;,
  4;19,27,28,20;,
  4;20,28,29,21;,
  4;21,29,30,22;,
  4;22,30,31,23;,
  4;23,31,32,24;,
  4;24,32,25,17;,
  4;25,33,34,26;,
  4;26,34,35,27;,
  4;27,35,36,28;,
  4;28,36,37,29;,
  4;29,37,38,30;,
  4;30,38,39,31;,
  4;31,39,40,32;,
  4;32,40,33,25;,
  4;33,41,42,34;,
  4;34,42,43,35;,
  4;35,43,44,36;,
  4;36,44,45,37;,
  4;37,45,46,38;,
  4;38,46,47,39;,
  4;39,47,48,40;,
  4;40,48,41,33;,
  4;41,49,50,42;,
  4;42,50,51,43;,
  4;43,51,52,44;,
  4;44,52,53,45;,
  4;45,53,54,46;,
  4;46,54,55,47;,
  4;47,55,56,48;,
  4;48,56,49,41;,
  4;49,57,58,50;,
  4;50,58,59,51;,
  4;51,59,60,52;,
  4;52,60,61,53;,
  4;53,61,62,54;,
  4;54,62,63,55;,
  4;55,63,64,56;,
  4;56,64,57,49;,
  4;57,65,66,58;,
  4;58,66,67,59;,
  4;59,67,68,60;,
  4;60,68,69,61;,
  4;61,69,70,62;,
  4;62,70,71,63;,
  4;63,71,72,64;,
  4;64,72,65,57;,
  4;65,73,74,66;,
  4;66,74,75,67;,
  4;67,75,76,68;,
  4;68,76,77,69;,
  4;69,77,78,70;,
  4;70,78,79,71;,
  4;71,79,80,72;,
  4;72,80,73,65;,
  3;73,81,74;,
  3;74,81,75;,
  3;75,81,76;,
  3;76,81,77;,
  3;77,81,78;,
  3;78,81,79;,
  3;79,81,80;,
  3;80,81,73;;
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
