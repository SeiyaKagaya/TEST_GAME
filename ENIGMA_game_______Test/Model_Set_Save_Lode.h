//============================================================================================
//
//とりあえずテキストでmodelセット状態のセーブとロード処理[Model_Set_Save_Lode.h]
// Author seiya kagaya
//
//============================================================================================

//初期化
void InitModel_SSL(void);

//テキストから配置物の情報を読み込む処理
void Model_DebugLoad(void);

//読み込んだモデルデータでセット
void Model_DebugSet(void);

//モデルセット状態をセーブ
void Model_DebugSave(void);

//モデル配置置き場
void NewSet_Debug_Model(void);