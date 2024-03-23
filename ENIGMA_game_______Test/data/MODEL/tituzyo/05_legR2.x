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
 53;
 -0.54941;0.26923;-2.18422;,
 0.61158;-0.74335;-3.54822;,
 -1.08870;0.58983;-3.97866;,
 -0.54941;0.26923;-2.18422;,
 1.05835;-1.00899;-2.06164;,
 -0.54941;0.26923;-2.18422;,
 0.56332;-0.52583;-0.64689;,
 -0.54941;0.26923;-2.18422;,
 -1.14695;0.85241;-0.47646;,
 -0.54941;0.26923;-2.18422;,
 -2.15716;1.54739;-2.30679;,
 -1.14695;0.85241;-0.47646;,
 -0.54941;0.26923;-2.18422;,
 -1.08870;0.58983;-3.97866;,
 -15.78472;-58.65161;-0.08228;,
 -14.81071;-58.63309;-1.71462;,
 -14.15405;-58.57356;0.89164;,
 -15.78472;-58.65161;-0.08228;,
 -14.15405;-58.57356;0.89164;,
 -16.75873;-58.67009;1.55008;,
 -15.78472;-58.65161;-0.08228;,
 -16.75873;-58.67009;1.55008;,
 -17.81885;-58.73731;-0.38002;,
 -15.78472;-58.65161;-0.08228;,
 -17.01191;-58.72196;-1.73231;,
 -15.78472;-58.65161;-0.08228;,
 -14.81071;-58.63309;-1.71462;,
 -1.90564;-20.57650;0.05515;,
 -3.60591;-19.24332;-0.37531;,
 -1.45885;-20.84214;1.54171;,
 -2.52732;-19.88454;3.21357;,
 -4.45098;-18.41856;2.03984;,
 -2.52732;-19.88454;3.21357;,
 -3.60591;-19.24332;-0.37531;,
 -4.45098;-18.41856;2.03984;,
 -14.62647;-39.48814;-1.46608;,
 -16.74026;-39.58104;-2.08004;,
 -14.24180;-39.45327;0.06062;,
 -15.04874;-39.46856;1.41291;,
 -17.24996;-39.55744;1.39523;,
 -18.31006;-39.62465;-0.53489;,
 -17.24996;-39.55744;1.39523;,
 -16.74026;-39.58104;-2.08004;,
 -14.38086;-52.50217;-1.38865;,
 -16.49464;-52.59509;-2.00260;,
 -13.99619;-52.46730;0.13806;,
 -14.80312;-52.48263;1.49035;,
 -17.00435;-52.57151;1.47265;,
 -18.06443;-52.63872;-0.45745;,
 -17.00435;-52.57151;1.47265;,
 -16.49464;-52.59509;-2.00260;,
 -14.81071;-58.63309;-1.71462;,
 -16.49464;-52.59509;-2.00260;;
 
 56;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,11;,
 3;12,13,10;,
 3;14,15,16;,
 3;17,18,19;,
 3;20,21,22;,
 3;23,22,24;,
 3;25,24,26;,
 3;1,27,28;,
 3;1,28,2;,
 3;4,29,27;,
 3;4,27,1;,
 3;6,30,29;,
 3;6,29,4;,
 3;8,30,6;,
 3;11,31,32;,
 3;10,31,11;,
 3;13,33,34;,
 3;13,34,10;,
 3;28,27,35;,
 3;28,35,36;,
 3;27,29,37;,
 3;27,37,35;,
 3;30,38,37;,
 3;30,37,29;,
 3;32,39,38;,
 3;31,39,32;,
 3;34,40,41;,
 3;33,42,40;,
 3;33,40,34;,
 3;35,43,44;,
 3;35,44,36;,
 3;37,45,43;,
 3;37,43,35;,
 3;38,46,45;,
 3;38,45,37;,
 3;39,47,46;,
 3;39,46,38;,
 3;40,48,49;,
 3;40,49,41;,
 3;42,50,48;,
 3;42,48,40;,
 3;43,51,44;,
 3;45,16,15;,
 3;45,15,43;,
 3;46,16,45;,
 3;47,19,18;,
 3;47,18,46;,
 3;48,22,21;,
 3;48,21,49;,
 3;50,24,22;,
 3;50,22,48;,
 3;52,26,24;;
 
 MeshMaterialList {
  14;
  56;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.097600;0.097600;0.097600;1.000000;;
   30.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\black_hair.jpg";
   }
  }
  Material {
   0.708800;0.693600;0.580000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   1.000000;
   0.000000;0.000000;0.000000;;
   0.190000;0.190000;0.190000;;
   TextureFilename {
    "data\\TEXTURE\\57583335.png";
   }
  }
  Material {
   0.442400;0.279200;0.184800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\texture_00130.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
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
    "data\\TEXTURE\\r00607.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.125600;0.483200;0.132000;1.000000;;
   5.000000;
   0.530000;0.530000;0.530000;;
   0.078500;0.302000;0.082500;;
   TextureFilename {
    "data\\TEXTURE\\metal02.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.184800;0.184800;0.184800;1.000000;;
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
    "data\\TEXTURE\\57583335_455x636.png";
   }
  }
  Material {
   0.558400;0.295200;0.147200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.432800;0.024800;0.075200;1.000000;;
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
    "data\\TEXTURE\\kuti.png";
   }
  }
 }
 MeshNormals {
  61;
  0.623837;0.780073;-0.048110;,
  0.623832;0.780077;-0.048112;,
  0.623839;0.780071;-0.048107;,
  0.819903;0.564728;0.094033;,
  0.819902;0.564730;0.094030;,
  0.623834;0.780075;-0.048111;,
  0.623829;0.780079;-0.048113;,
  0.170979;-0.135463;-0.975918;,
  0.150918;-0.124177;-0.980716;,
  0.936732;-0.282639;0.206514;,
  0.283664;-0.095610;0.954146;,
  -0.631961;0.281147;0.722206;,
  0.280635;-0.051234;-0.958446;,
  0.260867;-0.040134;-0.964540;,
  0.941274;-0.323794;0.095709;,
  0.847952;-0.163773;0.504138;,
  -0.394319;0.110354;0.912324;,
  -0.924322;0.272818;0.266830;,
  0.212862;-0.003577;-0.977076;,
  0.278260;0.015576;-0.960379;,
  0.989329;-0.002455;0.145678;,
  0.858193;0.030153;0.512440;,
  0.077979;-0.023638;0.996675;,
  -0.875891;-0.023988;0.481913;,
  0.040241;-0.999110;0.012677;,
  0.040243;-0.999109;0.012690;,
  0.040235;-0.999110;0.012696;,
  0.040234;-0.999110;0.012683;,
  0.040235;-0.999110;0.012673;,
  0.040238;-0.999110;0.012684;,
  0.098357;-0.189962;-0.976852;,
  0.098355;-0.189961;-0.976853;,
  0.933804;-0.175195;-0.311957;,
  0.886755;-0.357755;-0.292706;,
  0.933806;-0.175195;-0.311950;,
  0.572230;0.071560;0.816966;,
  -0.378245;0.208604;0.901895;,
  -0.820021;0.210108;0.532372;,
  -0.897085;0.018906;-0.441452;,
  -0.794525;0.361506;-0.487897;,
  -0.869023;0.195990;-0.454299;,
  -0.847196;-0.018261;-0.530967;,
  0.934758;-0.271360;-0.229326;,
  -0.006351;-0.041528;0.999117;,
  -0.696090;0.145323;-0.703094;,
  -0.686256;0.227766;-0.690778;,
  0.969707;-0.007109;-0.244167;,
  -0.006867;-0.028922;0.999558;,
  -0.876064;-0.018831;0.481826;,
  -0.759232;-0.001633;-0.650818;,
  -0.700947;-0.024069;-0.712807;,
  0.145112;-0.006718;-0.989392;,
  0.989254;-0.007555;0.146012;,
  0.968523;-0.054998;-0.242772;,
  0.244252;0.022146;0.969459;,
  0.121279;-0.038422;0.991874;,
  -0.875691;-0.029143;0.481992;,
  -0.875694;-0.029146;0.481987;,
  -0.857914;0.049872;-0.511367;,
  -0.786396;0.006366;-0.617690;,
  0.009839;-0.044900;-0.998943;;
  56;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,1,6;,
  3;29,24,25;,
  3;29,25,26;,
  3;29,26,27;,
  3;29,27,28;,
  3;29,28,24;,
  3;30,8,7;,
  3;30,7,31;,
  3;32,9,33;,
  3;32,33,34;,
  3;35,10,9;,
  3;4,9,3;,
  3;36,10,35;,
  3;36,11,10;,
  3;37,11,36;,
  3;38,39,40;,
  3;38,40,41;,
  3;7,8,13;,
  3;7,13,12;,
  3;33,9,14;,
  3;33,14,42;,
  3;10,15,14;,
  3;10,14,9;,
  3;10,16,43;,
  3;11,16,10;,
  3;11,17,16;,
  3;39,44,45;,
  3;39,17,40;,
  3;13,19,18;,
  3;13,18,12;,
  3;14,20,46;,
  3;14,46,42;,
  3;15,21,20;,
  3;15,20,14;,
  3;16,22,47;,
  3;16,47,43;,
  3;17,23,48;,
  3;17,48,16;,
  3;44,49,50;,
  3;44,50,45;,
  3;19,51,18;,
  3;20,52,53;,
  3;20,53,46;,
  3;21,52,20;,
  3;22,54,55;,
  3;22,55,47;,
  3;23,56,57;,
  3;23,57,48;,
  3;49,58,59;,
  3;49,59,50;,
  3;18,51,60;;
 }
 MeshTextureCoords {
  53;
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.625000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.187500;1.000000;,
  0.125000;1.000000;,
  0.250000;1.000000;,
  0.437500;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.687500;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.250000;,
  0.500000;0.250000;,
  0.875000;0.250000;,
  0.750000;0.250000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  0.625000;0.500000;,
  0.875000;0.500000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  0.625000;0.750000;,
  0.875000;0.750000;,
  0.000000;1.000000;,
  1.000000;0.750000;;
 }
}