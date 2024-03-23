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
 126;
 0.00000;17.11223;-11.55621;,
 5.77810;17.11223;-10.00798;,
 5.05012;16.79876;-8.74706;,
 0.00000;16.79876;-10.10024;,
 10.00798;17.11223;-5.77810;,
 8.74706;16.79876;-5.05012;,
 11.55621;17.11223;0.00000;,
 10.10024;16.79876;0.00000;,
 10.00798;17.11223;5.77810;,
 8.74706;16.79876;5.05012;,
 5.77810;17.11223;10.00798;,
 5.05012;16.79876;8.74706;,
 0.00000;17.11223;11.55621;,
 0.00000;16.79876;10.10024;,
 -5.77810;17.11223;10.00798;,
 -5.05012;16.79876;8.74706;,
 -10.00797;17.11223;5.77811;,
 -8.74706;16.79876;5.05012;,
 -11.55621;17.11223;0.00001;,
 -10.10024;16.79876;0.00001;,
 -10.00798;17.11223;-5.77810;,
 -8.74706;16.79876;-5.05012;,
 -5.77812;17.11223;-10.00797;,
 -5.05013;16.79876;-8.74706;,
 0.00000;17.11223;-11.55621;,
 0.00000;16.79876;-10.10024;,
 0.00000;18.79952;0.00000;,
 5.33492;18.79952;-9.24037;,
 0.00000;18.79952;-10.66985;,
 0.00000;18.79952;0.00000;,
 9.24037;18.79952;-5.33492;,
 0.00000;18.79952;0.00000;,
 10.66985;18.79952;0.00000;,
 0.00000;18.79952;0.00000;,
 9.24037;18.79952;5.33492;,
 0.00000;18.79952;0.00000;,
 5.33492;18.79952;9.24037;,
 0.00000;18.79952;0.00000;,
 0.00000;18.79952;10.66985;,
 0.00000;18.79952;0.00000;,
 -5.33492;18.79952;9.24037;,
 0.00000;18.79952;0.00000;,
 -9.24037;18.79952;5.33493;,
 0.00000;18.79952;0.00000;,
 -10.66985;18.79952;0.00001;,
 0.00000;18.79952;0.00000;,
 -9.24037;18.79952;-5.33492;,
 0.00000;18.79952;0.00000;,
 -5.33494;18.79952;-9.24037;,
 0.00000;18.79952;0.00000;,
 0.00000;18.79952;-10.66985;,
 0.00000;0.73339;0.00000;,
 0.00000;0.73339;-7.52547;,
 3.76274;0.73339;-6.51725;,
 0.00000;0.73339;0.00000;,
 6.51725;0.73339;-3.76274;,
 0.00000;0.73339;0.00000;,
 7.52547;0.73339;0.00000;,
 0.00000;0.73339;0.00000;,
 6.51725;0.73339;3.76274;,
 0.00000;0.73339;0.00000;,
 3.76274;0.73339;6.51725;,
 0.00000;0.73339;0.00000;,
 0.00000;0.73339;7.52547;,
 0.00000;0.73339;0.00000;,
 -3.76274;0.73339;6.51725;,
 0.00000;0.73339;0.00000;,
 -6.51725;0.73339;3.76274;,
 0.00000;0.73339;0.00000;,
 -7.52547;0.73339;0.00001;,
 0.00000;0.73339;0.00000;,
 -6.51726;0.73339;-3.76273;,
 0.00000;0.73339;0.00000;,
 -3.76274;0.73339;-6.51725;,
 0.00000;0.73339;0.00000;,
 0.00000;0.73339;-7.52547;,
 5.33492;20.68833;-9.24037;,
 9.24037;20.68833;-5.33492;,
 0.00000;20.68833;-10.66985;,
 10.66985;20.68833;0.00000;,
 0.00000;20.68833;-10.66985;,
 -5.33494;20.68833;-9.24037;,
 9.24037;20.68833;5.33492;,
 -9.24037;20.68833;-5.33492;,
 5.33492;20.68833;9.24037;,
 -10.66985;20.68833;0.00001;,
 0.00000;20.68833;10.66985;,
 -9.24037;20.68833;5.33493;,
 -5.33492;20.68833;9.24037;,
 5.77810;20.68989;-10.00798;,
 10.00798;20.68989;-5.77810;,
 0.00000;20.68989;-11.55621;,
 11.55621;20.68989;0.00000;,
 0.00000;20.68989;-11.55621;,
 -5.77812;20.68989;-10.00797;,
 10.00798;20.68989;5.77810;,
 -10.00798;20.68989;-5.77810;,
 5.77810;20.68989;10.00798;,
 -11.55621;20.68989;0.00001;,
 0.00000;20.68989;11.55621;,
 -10.00797;20.68989;5.77811;,
 -5.77810;20.68989;10.00798;,
 0.00000;-0.19209;7.63541;,
 -3.81770;-0.19209;6.61245;,
 3.81770;-0.19209;6.61245;,
 -6.61245;-0.19209;3.81770;,
 6.61245;-0.19209;3.81770;,
 -7.63541;-0.19209;0.00001;,
 7.63541;-0.19209;-0.00000;,
 -6.61245;-0.19209;-3.81770;,
 6.61245;-0.19209;-3.81770;,
 -3.81770;-0.19209;-6.61245;,
 3.81770;-0.19209;-6.61245;,
 0.00000;-0.19209;-7.63541;,
 4.30405;-0.17757;7.45484;,
 0.00000;-0.17757;8.60811;,
 7.45484;-0.17757;4.30405;,
 -4.30405;-0.17757;7.45484;,
 8.60811;-0.17757;-0.00000;,
 -7.45484;-0.17757;4.30405;,
 7.45484;-0.17757;-4.30405;,
 -8.60811;-0.17757;0.00001;,
 4.30405;-0.17757;-7.45484;,
 -7.45484;-0.17757;-4.30405;,
 0.00000;-0.17757;-8.60811;,
 -4.30406;-0.17757;-7.45484;;
 
 108;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;20,22,23,21;,
 4;22,24,25,23;,
 3;26,27,28;,
 3;29,30,27;,
 3;31,32,30;,
 3;33,34,32;,
 3;35,36,34;,
 3;37,38,36;,
 3;39,40,38;,
 3;41,42,40;,
 3;43,44,42;,
 3;45,46,44;,
 3;47,48,46;,
 3;49,50,48;,
 3;51,52,53;,
 3;54,53,55;,
 3;56,55,57;,
 3;58,57,59;,
 3;60,59,61;,
 3;62,61,63;,
 3;64,63,65;,
 3;66,65,67;,
 3;68,67,69;,
 3;70,69,71;,
 3;72,71,73;,
 3;74,73,75;,
 4;76,27,30,77;,
 4;76,78,28,27;,
 4;77,30,32,79;,
 4;80,81,48,50;,
 4;79,32,34,82;,
 4;81,83,46,48;,
 4;82,34,36,84;,
 4;83,85,44,46;,
 4;84,36,38,86;,
 4;85,87,42,44;,
 4;86,38,40,88;,
 4;87,88,40,42;,
 4;89,76,77,90;,
 4;89,90,4,1;,
 4;89,1,0,91;,
 4;89,91,78,76;,
 4;90,77,79,92;,
 4;90,92,6,4;,
 4;93,24,22,94;,
 4;93,94,81,80;,
 4;92,79,82,95;,
 4;92,95,8,6;,
 4;94,22,20,96;,
 4;94,96,83,81;,
 4;95,82,84,97;,
 4;95,97,10,8;,
 4;96,20,18,98;,
 4;96,98,85,83;,
 4;97,84,86,99;,
 4;97,99,12,10;,
 4;98,18,16,100;,
 4;98,100,87,85;,
 4;99,86,88,101;,
 4;99,101,14,12;,
 4;100,16,14,101;,
 4;100,101,88,87;,
 4;102,103,65,63;,
 4;102,63,61,104;,
 4;103,105,67,65;,
 4;104,61,59,106;,
 4;105,107,69,67;,
 4;106,59,57,108;,
 4;107,109,71,69;,
 4;108,57,55,110;,
 4;109,111,73,71;,
 4;110,55,53,112;,
 4;111,113,52,73;,
 4;112,53,52,113;,
 4;114,11,13,115;,
 4;114,115,102,104;,
 4;114,104,106,116;,
 4;114,116,9,11;,
 4;115,13,15,117;,
 4;115,117,103,102;,
 4;116,106,108,118;,
 4;116,118,7,9;,
 4;117,15,17,119;,
 4;117,119,105,103;,
 4;118,108,110,120;,
 4;118,120,5,7;,
 4;119,17,19,121;,
 4;119,121,107,105;,
 4;120,110,112,122;,
 4;120,122,2,5;,
 4;121,19,21,123;,
 4;121,123,109,107;,
 4;122,112,113,124;,
 4;122,124,3,2;,
 4;123,21,23,125;,
 4;123,125,111,109;,
 4;124,113,111,125;,
 4;124,125,23,3;;
 
 MeshMaterialList {
  2;
  108;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
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
   0.615200;0.304000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.310400;0.135200;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  86;
  0.000000;1.000000;0.000000;,
  -0.000000;-0.977599;-0.210477;,
  0.105238;-0.977599;-0.182278;,
  0.182278;-0.977599;-0.105238;,
  0.210476;-0.977599;-0.000000;,
  0.182278;-0.977599;0.105238;,
  0.105238;-0.977599;0.182278;,
  0.000000;-0.977599;0.210476;,
  -0.105238;-0.977599;0.182278;,
  -0.182278;-0.977599;0.105238;,
  -0.210477;-0.977599;0.000000;,
  -0.182278;-0.977599;-0.105238;,
  -0.105238;-0.977599;-0.182278;,
  0.000000;-1.000000;0.000000;,
  -0.499999;0.000000;0.866026;,
  -0.866026;0.000000;0.499999;,
  -0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.500000;0.000000;0.866025;,
  -0.866026;0.000000;-0.499999;,
  0.866026;0.000000;0.499999;,
  -0.499999;0.000000;-0.866026;,
  1.000000;0.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.866026;0.000000;-0.500000;,
  0.499999;0.000000;-0.866026;,
  -0.000881;0.999998;0.001527;,
  -0.001527;0.999998;0.000881;,
  -0.000000;0.000000;-1.000000;,
  -0.001763;0.999998;0.000000;,
  -0.500000;0.000000;-0.866025;,
  -0.001527;0.999998;-0.000881;,
  -0.866026;0.000000;-0.499999;,
  -0.000881;0.999998;-0.001527;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.999998;-0.001763;,
  -0.866026;0.000000;0.500000;,
  0.000881;0.999998;-0.001527;,
  0.000000;-0.117954;-0.993019;,
  0.496510;-0.117954;-0.859980;,
  -0.496510;-0.117952;-0.859980;,
  0.859979;-0.117955;-0.496510;,
  -0.859980;-0.117952;-0.496510;,
  0.993019;-0.117953;-0.000001;,
  -0.993019;-0.117954;0.000000;,
  0.859980;-0.117950;0.496510;,
  -0.859980;-0.117952;0.496510;,
  0.496510;-0.117954;0.859980;,
  -0.496510;-0.117952;0.859980;,
  0.000000;-0.117955;0.993019;,
  0.498080;-0.087557;0.862699;,
  0.000000;-0.087557;0.996159;,
  0.012930;-0.999889;0.007465;,
  -0.498080;-0.087557;0.862700;,
  0.014930;-0.999889;-0.000000;,
  -0.862699;-0.087557;0.498080;,
  0.012930;-0.999889;-0.007465;,
  -0.996159;-0.087557;0.000000;,
  0.007465;-0.999889;-0.012930;,
  -0.862700;-0.087557;-0.498079;,
  0.000000;-0.999889;-0.014930;,
  -0.498080;-0.087557;-0.862699;,
  0.499999;0.000000;-0.866026;,
  0.866026;0.000000;-0.499999;,
  0.000000;0.999998;0.001763;,
  1.000000;0.000000;0.000000;,
  0.000881;0.999998;0.001527;,
  0.866026;0.000000;0.499999;,
  0.001527;0.999998;0.000881;,
  0.499999;0.000000;0.866026;,
  0.001763;0.999998;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.001527;0.999998;-0.000881;,
  -0.499999;0.000000;0.866026;,
  0.007465;-0.999889;0.012930;,
  0.000000;-0.999889;0.014930;,
  0.862699;-0.087557;0.498080;,
  -0.007465;-0.999889;0.012930;,
  0.996159;-0.087557;-0.000000;,
  -0.012930;-0.999889;0.007465;,
  0.862699;-0.087557;-0.498080;,
  -0.014930;-0.999889;0.000000;,
  0.498080;-0.087557;-0.862699;,
  -0.012930;-0.999889;-0.007465;,
  0.000000;-0.087557;-0.996159;,
  -0.007465;-0.999889;-0.012930;;
  108;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,1,1,12;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  3;13,13,13;,
  4;14,14,15,15;,
  4;14,16,16,14;,
  4;15,15,17,17;,
  4;16,18,18,16;,
  4;17,17,19,19;,
  4;18,20,20,18;,
  4;19,19,21,21;,
  4;20,22,22,20;,
  4;21,21,23,23;,
  4;22,24,24,22;,
  4;23,23,25,25;,
  4;24,25,25,24;,
  4;26,26,27,27;,
  4;62,63,63,62;,
  4;62,62,28,28;,
  4;26,64,64,26;,
  4;27,27,29,29;,
  4;63,65,65,63;,
  4;28,28,30,30;,
  4;64,66,66,64;,
  4;29,29,31,31;,
  4;65,67,67,65;,
  4;30,30,32,32;,
  4;66,68,68,66;,
  4;31,31,33,33;,
  4;67,69,69,67;,
  4;32,32,34,34;,
  4;68,70,70,68;,
  4;33,33,35,35;,
  4;69,71,71,69;,
  4;34,34,36,36;,
  4;70,72,72,70;,
  4;35,35,37,37;,
  4;71,73,73,71;,
  4;36,36,73,73;,
  4;72,37,37,72;,
  4;38,39,39,38;,
  4;38,38,40,40;,
  4;39,41,41,39;,
  4;40,40,42,42;,
  4;41,43,43,41;,
  4;42,42,44,44;,
  4;43,45,45,43;,
  4;44,44,46,46;,
  4;45,47,47,45;,
  4;46,46,48,48;,
  4;47,49,49,47;,
  4;48,48,49,49;,
  4;50,50,51,51;,
  4;74,75,75,74;,
  4;74,74,52,52;,
  4;50,76,76,50;,
  4;51,51,53,53;,
  4;75,77,77,75;,
  4;52,52,54,54;,
  4;76,78,78,76;,
  4;53,53,55,55;,
  4;77,79,79,77;,
  4;54,54,56,56;,
  4;78,80,80,78;,
  4;55,55,57,57;,
  4;79,81,81,79;,
  4;56,56,58,58;,
  4;80,82,82,80;,
  4;57,57,59,59;,
  4;81,83,83,81;,
  4;58,58,60,60;,
  4;82,84,84,82;,
  4;59,59,61,61;,
  4;83,85,85,83;,
  4;60,60,85,85;,
  4;84,61,61,84;;
 }
 MeshTextureCoords {
  126;
  0.000000;0.250000;,
  0.083330;0.250000;,
  0.083330;0.500000;,
  0.000000;0.500000;,
  0.166670;0.250000;,
  0.166670;0.500000;,
  0.250000;0.250000;,
  0.250000;0.500000;,
  0.333330;0.250000;,
  0.333330;0.500000;,
  0.416670;0.250000;,
  0.416670;0.500000;,
  0.500000;0.250000;,
  0.500000;0.500000;,
  0.583330;0.250000;,
  0.583330;0.500000;,
  0.666670;0.250000;,
  0.666670;0.500000;,
  0.750000;0.250000;,
  0.750000;0.500000;,
  0.833330;0.250000;,
  0.833330;0.500000;,
  0.916670;0.250000;,
  0.916670;0.500000;,
  1.000000;0.250000;,
  1.000000;0.500000;,
  0.041670;0.000000;,
  0.083330;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.166670;0.000000;,
  0.208330;0.000000;,
  0.250000;0.000000;,
  0.291670;0.000000;,
  0.333330;0.000000;,
  0.375000;0.000000;,
  0.416670;0.000000;,
  0.458330;0.000000;,
  0.500000;0.000000;,
  0.541670;0.000000;,
  0.583330;0.000000;,
  0.625000;0.000000;,
  0.666670;0.000000;,
  0.708330;0.000000;,
  0.750000;0.000000;,
  0.791670;0.000000;,
  0.833330;0.000000;,
  0.875000;0.000000;,
  0.916670;0.000000;,
  0.958330;0.000000;,
  1.000000;0.000000;,
  0.041670;1.000000;,
  0.000000;1.000000;,
  0.083330;1.000000;,
  0.125000;1.000000;,
  0.166670;1.000000;,
  0.208330;1.000000;,
  0.250000;1.000000;,
  0.291670;1.000000;,
  0.333330;1.000000;,
  0.375000;1.000000;,
  0.416670;1.000000;,
  0.458330;1.000000;,
  0.500000;1.000000;,
  0.541670;1.000000;,
  0.583330;1.000000;,
  0.625000;1.000000;,
  0.666670;1.000000;,
  0.708330;1.000000;,
  0.750000;1.000000;,
  0.791670;1.000000;,
  0.833330;1.000000;,
  0.875000;1.000000;,
  0.916670;1.000000;,
  0.958330;1.000000;,
  1.000000;1.000000;,
  0.083330;0.045680;,
  0.166670;0.045680;,
  0.000000;0.045680;,
  0.250000;0.045680;,
  1.000000;0.045680;,
  0.916670;0.045680;,
  0.333330;0.045680;,
  0.833330;0.045680;,
  0.416670;0.045680;,
  0.750000;0.045680;,
  0.500000;0.045680;,
  0.666670;0.045680;,
  0.583330;0.045680;,
  0.083330;0.095210;,
  0.166670;0.095210;,
  0.000000;0.095210;,
  0.250000;0.095210;,
  1.000000;0.095210;,
  0.916670;0.095210;,
  0.333330;0.095210;,
  0.833330;0.095210;,
  0.416670;0.095210;,
  0.750000;0.095210;,
  0.500000;0.095210;,
  0.666670;0.095210;,
  0.583330;0.095210;,
  0.500000;0.963960;,
  0.583330;0.963960;,
  0.416670;0.963960;,
  0.666670;0.963960;,
  0.333330;0.963960;,
  0.750000;0.963960;,
  0.250000;0.963960;,
  0.833330;0.963960;,
  0.166670;0.963960;,
  0.916670;0.963960;,
  0.083330;0.963960;,
  0.000000;0.963960;,
  0.416670;0.938340;,
  0.500000;0.938340;,
  0.333330;0.938340;,
  0.583330;0.938340;,
  0.250000;0.938340;,
  0.666670;0.938340;,
  0.166670;0.938340;,
  0.750000;0.938340;,
  0.083330;0.938340;,
  0.833330;0.938340;,
  0.000000;0.938340;,
  0.916670;0.938340;;
 }
}
