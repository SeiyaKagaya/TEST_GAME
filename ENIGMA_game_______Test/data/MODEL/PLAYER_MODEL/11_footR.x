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
 79;
 0.26349;-3.73239;-0.90374;,
 1.95670;0.20998;-2.37914;,
 0.26349;0.46752;-2.71322;,
 0.26349;-3.73239;-0.90374;,
 2.65807;-0.28541;0.09075;,
 0.26349;-3.73239;-0.90374;,
 1.80362;-4.03195;1.77538;,
 0.26349;-3.73239;-0.90374;,
 0.26349;-4.03195;2.88511;,
 0.26349;-3.73239;-0.90374;,
 -1.27666;-4.03195;1.77538;,
 0.26349;-3.73239;-0.90374;,
 -2.13109;-0.28541;0.09075;,
 0.26349;-3.73239;-0.90374;,
 -1.42974;0.20998;-2.37914;,
 0.26349;-3.73239;-0.90374;,
 0.26349;0.46752;-2.71322;,
 3.10928;-1.96638;-5.85411;,
 0.26349;-1.96638;-7.90461;,
 3.23235;-0.91463;-0.39379;,
 2.36278;-0.35623;3.25802;,
 0.26349;-0.35623;4.79381;,
 -1.83582;-0.35623;3.25802;,
 -2.70538;-0.91463;-0.39379;,
 -2.58232;-1.96638;-5.85411;,
 0.26349;-1.96638;-7.90461;,
 3.98170;-3.24298;-7.37170;,
 0.26349;-3.24298;-10.05084;,
 5.04544;-3.24298;-0.90374;,
 3.98170;-3.24298;5.59562;,
 0.26349;-3.24298;6.98187;,
 -3.45474;-3.24298;5.59562;,
 -4.53081;-3.24298;-0.90374;,
 -3.45474;-3.24298;-7.37170;,
 0.26349;-3.24298;-10.05084;,
 3.94196;-4.74734;-7.34736;,
 0.26295;-4.74734;-9.77892;,
 5.03036;-4.74734;-0.94761;,
 3.94196;-4.74734;5.48087;,
 0.26295;-4.74734;6.94986;,
 -3.41605;-4.74734;5.48087;,
 -4.51572;-4.74734;-0.94761;,
 -3.41605;-4.74734;-7.34736;,
 0.26295;-4.74734;-9.77892;,
 3.43230;-4.74066;-6.50031;,
 0.26257;-4.74066;-8.78423;,
 4.33910;-4.74066;-0.98649;,
 3.43230;-4.74066;4.55411;,
 0.26257;-4.74066;5.73585;,
 -2.90715;-4.74066;4.55411;,
 -3.82449;-4.74066;-0.98649;,
 -2.90715;-4.74066;-6.50031;,
 0.26257;-4.74066;-8.78423;,
 2.68857;-4.71449;-5.20659;,
 0.26257;-4.71449;-6.95462;,
 3.69346;-4.71449;-0.98649;,
 2.68857;-4.71449;3.23362;,
 0.26257;-4.71449;5.00841;,
 -2.16342;-4.71449;3.23362;,
 -3.16830;-4.71449;-0.98649;,
 -2.16342;-4.71449;-5.20659;,
 0.26257;-4.71449;-6.95462;,
 1.57552;-4.72983;-3.27039;,
 0.26257;-4.72983;-4.21642;,
 2.11934;-4.72983;-0.98649;,
 1.57552;-4.72983;1.29742;,
 0.26257;-4.72983;2.24343;,
 -1.05037;-4.72983;1.29742;,
 -1.59421;-4.72983;-0.98649;,
 -1.05037;-4.72983;-3.27039;,
 0.26257;-4.72983;-4.21642;,
 0.26257;-4.73937;-0.98649;,
 0.26257;-4.73937;-0.98649;,
 0.26257;-4.73937;-0.98649;,
 0.26257;-4.73937;-0.98649;,
 0.26257;-4.73937;-0.98649;,
 0.26257;-4.73937;-0.98649;,
 0.26257;-4.73937;-0.98649;,
 0.26257;-4.73937;-0.98649;;
 
 64;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;36,35,44,45;,
 4;35,37,46,44;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;45,44,53,54;,
 4;44,46,55,53;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;54,53,62,63;,
 4;53,55,64,62;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 3;63,62,71;,
 3;62,64,72;,
 3;64,65,73;,
 3;65,66,74;,
 3;66,67,75;,
 3;67,68,76;,
 3;68,69,77;,
 3;69,70,78;;
 
 MeshMaterialList {
  7;
  64;
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
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
  81;
  -0.398418;0.640328;0.656691;,
  -0.000001;0.395676;0.918390;,
  -0.527137;0.487014;0.696379;,
  -0.675427;0.674084;0.299013;,
  -0.577222;0.768844;0.275126;,
  0.000000;0.996889;0.078818;,
  0.097728;0.994447;0.039030;,
  0.675429;0.674082;0.299013;,
  0.527137;0.487016;0.696378;,
  0.000001;0.876908;-0.480658;,
  0.550289;0.779171;-0.300124;,
  0.775249;0.630584;-0.036795;,
  -0.455668;0.779042;-0.430651;,
  -0.542137;0.385382;-0.746705;,
  0.455670;0.779040;-0.430652;,
  0.249671;0.968329;-0.001622;,
  -0.549781;0.779465;-0.300291;,
  0.000001;0.859453;-0.511214;,
  0.786242;0.398176;-0.472525;,
  0.949436;0.313949;-0.002689;,
  0.750836;0.341189;0.565540;,
  -0.000001;0.347620;0.937636;,
  -0.750242;0.341606;0.566076;,
  -0.949074;0.315042;-0.002759;,
  -0.785521;0.398800;-0.473196;,
  0.565873;-0.086847;-0.819906;,
  0.843008;-0.056380;-0.534938;,
  0.999757;-0.022056;-0.000395;,
  0.774643;-0.044209;0.630851;,
  -0.000003;-0.053709;0.998557;,
  -0.774092;-0.043894;0.631549;,
  -0.999763;-0.021749;-0.000399;,
  -0.842547;-0.055947;-0.535710;,
  0.000001;-0.999948;0.010205;,
  -0.014604;-0.999867;0.007288;,
  -0.021907;-0.999760;0.000013;,
  -0.014440;-0.999847;-0.009848;,
  0.000002;-0.999882;-0.015359;,
  0.014350;-0.999849;-0.009847;,
  0.021723;-0.999764;0.000013;,
  0.014514;-0.999868;0.007279;,
  0.000000;-0.999991;0.004350;,
  -0.007613;-0.999965;0.003363;,
  -0.012081;-0.999927;0.000005;,
  -0.007982;-0.999950;-0.006039;,
  0.000000;-0.999953;-0.009710;,
  0.007891;-0.999951;-0.006024;,
  0.011901;-0.999929;0.000005;,
  0.007523;-0.999966;0.003349;,
  -0.000000;-0.999991;-0.004278;,
  0.005262;-0.999982;-0.003025;,
  0.007441;-0.999972;-0.000000;,
  0.005264;-0.999982;0.003018;,
  -0.000000;-0.999991;0.004264;,
  -0.005264;-0.999982;0.003018;,
  -0.007441;-0.999972;-0.000000;,
  -0.005262;-0.999982;-0.003025;,
  -0.000000;-1.000000;-0.000000;,
  0.497660;0.836044;0.231008;,
  0.056700;0.995285;0.078691;,
  0.775666;0.397378;0.490340;,
  0.000001;0.892819;-0.450415;,
  0.525340;0.802909;-0.281700;,
  0.741242;0.663700;-0.100313;,
  -0.249662;0.968332;-0.001623;,
  0.542132;0.385383;-0.746708;,
  -0.741239;0.663704;-0.100310;,
  -0.525338;0.802911;-0.281698;,
  -0.774435;0.631577;-0.036879;,
  0.625402;0.653140;0.426942;,
  0.000001;0.691185;0.722678;,
  -0.624736;0.653637;0.427157;,
  -0.565893;-0.086450;-0.819934;,
  0.000001;-0.999981;0.006106;,
  -0.007090;-0.999967;0.003888;,
  -0.009907;-0.999951;0.000017;,
  -0.006018;-0.999975;-0.003670;,
  0.000004;-0.999984;-0.005722;,
  0.006019;-0.999975;-0.003697;,
  0.009900;-0.999951;0.000017;,
  0.007089;-0.999967;0.003898;;
  64;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;58,5,59;,
  3;0,6,5;,
  3;60,7,60;,
  3;58,8,7;,
  3;0,1,8;,
  4;61,62,10,9;,
  4;62,63,11,10;,
  4;3,4,12,64;,
  4;13,13,13,12;,
  4;65,65,14,65;,
  4;6,7,15,14;,
  4;66,67,16,68;,
  4;67,61,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,69,20,19;,
  4;69,70,21,20;,
  4;70,71,22,21;,
  4;71,68,23,22;,
  4;68,16,24,23;,
  4;16,9,17,24;,
  4;25,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,72,72,32;,
  4;73,74,34,33;,
  4;74,75,35,34;,
  4;75,76,36,35;,
  4;76,77,37,36;,
  4;77,78,38,37;,
  4;78,79,39,38;,
  4;79,80,40,39;,
  4;80,73,33,40;,
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
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;;
 }
 MeshTextureCoords {
  79;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}