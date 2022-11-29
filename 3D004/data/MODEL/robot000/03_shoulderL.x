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
 107;
 -0.77950;10.79320;-10.79320;,
 -0.77950;10.79320;10.79320;,
 0.77940;10.79320;10.79320;,
 0.77940;10.79320;-10.79320;,
 -0.77950;-10.79320;10.79320;,
 -0.77950;-10.79320;-10.79320;,
 0.77940;-10.57460;-10.79320;,
 0.77940;-10.57460;10.79320;,
 22.33090;9.87530;-10.81340;,
 21.71600;10.50580;-10.81340;,
 21.71600;10.50580;10.71110;,
 22.33090;9.87530;10.71110;,
 -0.77950;-10.79320;10.79320;,
 -0.77950;10.79320;10.79320;,
 -0.77950;10.79320;-10.79320;,
 -0.77950;-10.79320;-10.79320;,
 -0.77950;-9.35660;-13.25910;,
 -0.77950;-10.79320;-11.82250;,
 -0.77950;9.35660;-13.25910;,
 -0.77950;10.79320;-11.82250;,
 -0.77950;-10.79320;11.86890;,
 -0.77950;10.79320;11.86890;,
 -0.77950;9.35660;13.30540;,
 -0.77950;-9.35660;13.30540;,
 0.77940;-10.57460;-10.79320;,
 0.77940;8.41600;-10.79320;,
 0.77940;8.41600;10.79320;,
 0.77940;-10.57460;10.79320;,
 22.71010;8.27630;-10.81340;,
 22.71010;8.27630;10.71110;,
 20.17590;10.73580;10.71930;,
 21.71600;10.50580;10.71110;,
 21.71600;10.50580;-10.81340;,
 20.17590;10.73580;-10.81140;,
 0.77940;-10.57460;-10.79320;,
 19.04860;-7.46830;-10.81340;,
 22.71010;8.27630;-10.81340;,
 0.77940;8.41600;-10.79320;,
 0.77940;8.41600;10.79320;,
 22.71010;8.27630;10.71110;,
 19.04860;-7.46830;10.71110;,
 0.77940;-10.57460;10.79320;,
 22.71010;8.27630;-10.81340;,
 22.71010;8.27630;10.71110;,
 -0.77950;-9.35660;-13.25910;,
 0.64790;-9.35820;-13.25910;,
 0.77940;-10.79320;-11.82320;,
 -0.77950;-10.79320;-11.82250;,
 17.86930;-6.24340;-12.80630;,
 19.04860;-7.46830;-11.34260;,
 0.76250;10.79320;-11.82250;,
 20.17590;10.73580;-11.38110;,
 20.06570;9.30190;-12.82130;,
 0.77720;9.35660;-13.25910;,
 -0.77950;9.35660;-13.25910;,
 -0.77950;10.79320;-11.82250;,
 -0.77950;9.35660;13.30540;,
 0.77720;9.35660;13.30540;,
 0.75870;10.79320;11.86890;,
 -0.77950;10.79320;11.86890;,
 20.06630;9.30570;12.76840;,
 20.17590;10.73580;11.32710;,
 0.77940;-10.79320;11.86970;,
 19.04860;-7.46830;11.28000;,
 17.87350;-6.24730;12.74970;,
 0.64790;-9.35840;13.30540;,
 -0.77950;-9.35660;13.30540;,
 -0.77950;-10.79320;11.86890;,
 21.71600;10.50580;-11.33890;,
 21.02590;9.17040;-12.79610;,
 22.71010;8.27630;-11.34480;,
 21.24080;8.27320;-12.79800;,
 22.33090;9.87530;-11.34480;,
 21.02030;9.16520;12.73520;,
 21.71600;10.50580;11.27540;,
 21.03190;9.17140;12.73990;,
 22.33090;9.87530;11.28290;,
 21.24480;8.27330;12.73970;,
 22.71010;8.27630;11.28270;,
 0.77940;8.63450;-13.25910;,
 0.77940;8.63450;13.30540;,
 -0.77950;-10.79320;-11.82250;,
 0.77940;-10.79320;-11.82320;,
 22.33090;9.87530;-11.34480;,
 21.71600;10.50580;-11.33890;,
 0.76250;10.79320;-11.82250;,
 -0.77950;10.79320;-11.82250;,
 -0.77950;10.79320;11.86890;,
 0.75870;10.79320;11.86890;,
 21.71600;10.50580;11.27540;,
 22.33090;9.87530;11.28290;,
 0.77940;-10.79320;11.86970;,
 -0.77950;-10.79320;11.86890;,
 19.04860;-7.46830;-10.81340;,
 19.04860;-7.46830;-11.34260;,
 22.71010;8.27630;-11.34480;,
 22.71010;8.27630;11.28270;,
 19.04860;-7.46830;11.28000;,
 19.04860;-7.46830;10.71110;,
 21.71600;10.50580;-11.33890;,
 20.17590;10.73580;-11.38110;,
 20.17590;10.73580;11.32710;,
 21.71600;10.50580;11.27540;,
 19.04860;-7.46830;-11.34260;,
 19.04860;-7.46830;-10.81340;,
 19.04860;-7.46830;10.71110;,
 19.04860;-7.46830;11.28000;;
 
 66;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 3;16,17,18;,
 3;18,17,19;,
 3;19,17,14;,
 3;14,17,15;,
 3;12,20,13;,
 3;13,20,21;,
 3;21,20,22;,
 3;22,20,23;,
 4;24,25,26,27;,
 4;25,28,29,26;,
 4;30,31,32,33;,
 4;34,35,36,37;,
 4;38,39,40,41;,
 4;2,30,33,3;,
 4;42,8,11,43;,
 4;44,45,46,47;,
 4;45,48,49,46;,
 4;50,51,52,53;,
 4;53,54,55,50;,
 4;56,57,58,59;,
 4;57,60,61,58;,
 4;62,63,64,65;,
 4;65,66,67,62;,
 4;51,68,69,52;,
 4;70,49,48,71;,
 4;71,69,72,70;,
 3;69,68,72;,
 4;60,73,74,61;,
 4;73,75,76,74;,
 4;75,77,78,76;,
 4;63,78,77,64;,
 3;44,54,45;,
 3;54,53,45;,
 3;45,53,79;,
 3;56,66,57;,
 3;66,65,57;,
 3;57,65,80;,
 4;5,81,82,6;,
 4;83,84,9,8;,
 4;3,85,86,0;,
 4;1,87,88,2;,
 4;10,89,90,11;,
 4;7,91,92,4;,
 4;93,94,95,42;,
 4;96,97,98,43;,
 4;33,32,99,100;,
 3;71,79,69;,
 3;69,79,52;,
 3;52,79,53;,
 3;57,80,60;,
 3;80,77,60;,
 3;60,77,73;,
 3;73,77,75;,
 4;101,102,31,30;,
 4;79,71,48,45;,
 4;82,103,104,6;,
 4;7,105,106,91;,
 4;65,64,77,80;,
 4;88,101,30,2;,
 4;3,33,100,85;,
 4;95,83,8,42;,
 4;90,96,43,11;;
 
 MeshMaterialList {
  6;
  66;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.648000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\gm_tex1.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\machingun.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\gm_tex2.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\gm_tex1.png";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\gm_tex3.png";
   }
  }
 }
 MeshNormals {
  59;
  0.103878;-0.993234;0.051924;,
  0.125960;-0.989635;0.068972;,
  0.000000;1.000000;0.000000;,
  0.001479;0.999999;-0.000006;,
  0.001479;0.999999;0.000007;,
  0.103913;-0.993342;-0.049743;,
  0.125851;-0.989846;-0.066080;,
  1.000000;0.000000;0.000000;,
  0.018630;-0.003091;-0.999822;,
  0.021361;0.000236;0.999772;,
  -0.006370;-0.999980;0.000000;,
  0.455634;0.890167;0.000000;,
  0.001036;-0.000134;0.999999;,
  -0.004116;0.000435;-0.999991;,
  0.075530;0.997144;0.000007;,
  0.075530;0.997144;-0.000006;,
  0.876208;0.481934;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.030138;-0.251284;-0.967444;,
  0.106101;-0.936538;-0.334125;,
  0.005698;0.923933;-0.382513;,
  0.008801;0.305226;-0.952239;,
  0.008845;0.252936;0.967443;,
  0.006660;0.924000;0.382334;,
  0.107018;-0.935780;0.335951;,
  0.038448;-0.303519;0.952049;,
  -1.000000;0.000000;0.000000;,
  0.049754;0.376490;-0.925084;,
  0.078042;0.920782;-0.382192;,
  0.921929;0.002355;-0.387353;,
  0.388924;0.002550;-0.921266;,
  0.301278;0.298926;-0.905469;,
  0.805625;0.445142;-0.390919;,
  0.052129;0.307293;0.950186;,
  0.081335;0.920576;0.382000;,
  0.271597;0.881752;0.385679;,
  -0.055547;0.384173;0.921589;,
  0.134096;0.335758;0.932355;,
  0.717202;0.559404;0.415559;,
  0.320986;-0.318992;-0.891747;,
  0.715238;-0.427150;-0.553152;,
  0.716876;-0.426809;0.551292;,
  0.325216;-0.319198;0.890139;,
  0.922571;0.001919;0.385821;,
  0.210893;-0.011408;0.977443;,
  0.420880;0.815928;-0.396385;,
  0.996778;0.080214;0.000000;,
  0.996778;0.080214;0.000000;,
  -0.000301;-0.382768;-0.923845;,
  0.037638;-0.941710;-0.334315;,
  0.000000;0.252725;-0.967538;,
  0.000000;0.923880;-0.382683;,
  0.000000;0.382667;0.923886;,
  0.000000;0.923873;0.382700;,
  -0.000224;-0.252770;0.967526;,
  0.037611;-0.940972;0.336388;,
  0.974009;-0.226512;-0.000000;,
  0.169740;-0.980108;0.102838;,
  0.169359;-0.980615;-0.098543;;
  66;
  4;2,2,4,3;,
  4;5,0,1,6;,
  4;16,11,11,16;,
  4;17,17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,17;,
  3;17,17,26;,
  4;7,7,7,7;,
  4;10,10,10,10;,
  4;14,11,11,15;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;4,14,15,3;,
  4;46,16,16,47;,
  4;48,18,19,49;,
  4;18,39,40,19;,
  4;20,28,27,21;,
  4;21,50,51,20;,
  4;52,22,23,53;,
  4;22,33,34,23;,
  4;24,41,42,25;,
  4;25,54,55,24;,
  4;28,45,31,27;,
  4;29,40,39,30;,
  4;30,31,32,29;,
  3;31,45,32;,
  4;33,36,35,34;,
  4;36,37,38,35;,
  4;37,44,43,38;,
  4;41,43,44,42;,
  3;48,50,18;,
  3;50,21,18;,
  3;18,21,8;,
  3;52,54,22;,
  3;54,25,22;,
  3;22,25,9;,
  4;0,49,19,1;,
  4;32,45,11,16;,
  4;3,20,51,2;,
  4;2,53,23,4;,
  4;11,35,38,16;,
  4;6,24,55,5;,
  4;56,40,29,46;,
  4;43,41,56,47;,
  4;15,11,45,28;,
  3;30,8,31;,
  3;31,8,27;,
  3;27,8,21;,
  3;22,9,33;,
  3;9,44,33;,
  3;33,44,36;,
  3;36,44,37;,
  4;34,35,11,14;,
  4;8,30,39,18;,
  4;19,57,57,1;,
  4;6,58,58,24;,
  4;25,42,44,9;,
  4;23,34,14,4;,
  4;3,15,28,20;,
  4;29,32,16,46;,
  4;38,43,47,16;;
 }
 MeshTextureCoords {
  107;
  0.734230;0.241380;,
  0.734230;0.161560;,
  0.740300;0.161560;,
  0.740300;0.241380;,
  0.868800;0.259910;,
  0.973170;0.259840;,
  0.973170;0.250840;,
  0.868800;0.250900;,
  0.868620;0.037510;,
  0.868620;0.033640;,
  0.973570;0.033640;,
  0.973570;0.037510;,
  0.699750;0.139160;,
  0.699750;0.035420;,
  0.615440;0.035420;,
  0.615440;0.139160;,
  0.605810;0.132260;,
  0.611420;0.139160;,
  0.605810;0.042330;,
  0.611420;0.035420;,
  0.703950;0.139160;,
  0.703950;0.035420;,
  0.709560;0.042330;,
  0.709560;0.132260;,
  0.895480;0.147350;,
  0.895480;0.073050;,
  0.945600;0.073050;,
  0.945600;0.147350;,
  0.895430;0.134770;,
  0.945410;0.134770;,
  0.815840;0.161830;,
  0.821840;0.161860;,
  0.821840;0.241460;,
  0.815840;0.241450;,
  0.890440;0.237650;,
  0.951650;0.225070;,
  0.963920;0.165530;,
  0.890440;0.164170;,
  0.890440;0.164170;,
  0.963920;0.165530;,
  0.951650;0.225070;,
  0.890440;0.237650;,
  0.868620;0.047330;,
  0.973570;0.047330;,
  0.728960;0.367580;,
  0.736140;0.367590;,
  0.736800;0.375440;,
  0.728960;0.375440;,
  0.822690;0.350560;,
  0.828620;0.357250;,
  0.736710;0.257380;,
  0.834280;0.257700;,
  0.833730;0.265540;,
  0.736780;0.265240;,
  0.728960;0.265240;,
  0.728960;0.257380;,
  0.843970;0.039520;,
  0.836270;0.039520;,
  0.836360;0.031790;,
  0.843970;0.031790;,
  0.740870;0.039790;,
  0.740320;0.032100;,
  0.836260;0.147970;,
  0.745900;0.130070;,
  0.751710;0.123500;,
  0.836910;0.140250;,
  0.843970;0.140240;,
  0.843970;0.147970;,
  0.842020;0.258960;,
  0.838550;0.266260;,
  0.847020;0.271150;,
  0.839630;0.271170;,
  0.845110;0.262400;,
  0.736150;0.040550;,
  0.732710;0.033330;,
  0.736090;0.040520;,
  0.729670;0.036730;,
  0.735040;0.045350;,
  0.727790;0.045330;,
  0.736800;0.269190;,
  0.836260;0.043410;,
  0.978150;0.259840;,
  0.978150;0.250830;,
  0.866030;0.037510;,
  0.866060;0.033640;,
  0.740230;0.245190;,
  0.734230;0.245190;,
  0.734230;0.157580;,
  0.740220;0.157580;,
  0.976320;0.033640;,
  0.976360;0.037510;,
  0.863590;0.250910;,
  0.863600;0.259910;,
  0.868620;0.143970;,
  0.866040;0.143970;,
  0.866030;0.047330;,
  0.976360;0.047330;,
  0.976340;0.143970;,
  0.973570;0.143970;,
  0.821840;0.243400;,
  0.815840;0.243560;,
  0.815840;0.159580;,
  0.821840;0.159780;,
  0.975760;0.145280;,
  0.973200;0.145290;,
  0.869130;0.145350;,
  0.866380;0.145350;;
 }
}
