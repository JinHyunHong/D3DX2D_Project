#include "stdafx.h"
#include "NameSelectScene.h"
#include "Scene/Layer/Layer.h"
#include "Actor.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/AnimatorComponent.h"
#include "Scene/Component/TextRendererComponent.h"
#include "Scene/Component/ColliderComponent.h"

NameSelectScene::NameSelectScene(Tool* const tool) :
	Scene(tool)
{
	auto text_layer = CreateLayer("Text");
	auto register_name = text_layer->CreateActor();
	register_name->SetName("RegisterName");
	register_name->AddComponent<MeshRendererComponent>();
	register_name->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.0f, 2.3f, 1.0f));
	register_name->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(75.0f, 85.0f, 0.0f));
	auto animator = register_name->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Xml/Animation/RegisterName.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("RegisterName");

	/*
		Selected_text
	*/
	select = text_layer->CreateActor();
	auto select_text = select->AddComponent<TextRendererComponent>();
	auto select_transfrom = select->GetComponent<TransformComponent>();
	select_transfrom->SetPosition(D3DXVECTOR3(85.0f, 205.0f, 0.0f));
	select_text->AddText("Base", " ", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	/*
		TextBoard
	*/
	board_layer = CreateLayer("board");
	auto A = board_layer->CreateActor();
	A->SetName("A");
	auto A_text = A->AddComponent<TextRendererComponent>();
	auto A_transfrom = A->GetComponent<TransformComponent>();
	A_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	A_transfrom->SetPosition(D3DXVECTOR3(100.0f, 270.0f, 0.0f));
	A_text->AddText("Base", "A", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	A->AddComponent<ColliderComponent>();

	auto B = board_layer->CreateActor();
	B->SetName("B");
	auto B_text = B->AddComponent<TextRendererComponent>();
	auto B_transfrom = B->GetComponent<TransformComponent>();
	B_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	B_transfrom->SetPosition(D3DXVECTOR3(130.0f, 270.0f, 0.0f));
	B_text->AddText("Base", "B", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	B->AddComponent<ColliderComponent>();

	auto C = board_layer->CreateActor();
	C->SetName("C");
	auto C_transfrom = C->GetComponent<TransformComponent>();
	C_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	C_transfrom->SetPosition(D3DXVECTOR3(160.0f, 270.0f, 0.0f));
	auto C_text = C->AddComponent<TextRendererComponent>();
	C_text->AddText("Base", "C", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	C->AddComponent<ColliderComponent>();

	auto D = board_layer->CreateActor();
	D->SetName("D");
	auto D_text = D->AddComponent<TextRendererComponent>(); 
	auto D_transfrom = D->GetComponent<TransformComponent>();
	D_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	D_transfrom->SetPosition(D3DXVECTOR3(190.0f, 270.0f, 0.0f));
	D->AddComponent<ColliderComponent>();
	D_text->AddText("Base", "D", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	auto E = board_layer->CreateActor();
	E->SetName("E");
	auto E_text = E->AddComponent<TextRendererComponent>();
	auto E_transfrom = E->GetComponent<TransformComponent>();
	E_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	E_transfrom->SetPosition(D3DXVECTOR3(220.0f, 270.0f, 0.0f));
	E->AddComponent<ColliderComponent>();
	E_text->AddText("Base", "E", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	auto F = board_layer->CreateActor();
	F->SetName("F");
	auto F_text = F->AddComponent<TextRendererComponent>();
	auto F_transfrom = F->GetComponent<TransformComponent>();
	F_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	F_transfrom->SetPosition(D3DXVECTOR3(250.0f, 270.0f, 0.0f));
	F->AddComponent<ColliderComponent>();
	F_text->AddText("Base", "F", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto G = board_layer->CreateActor();	
	G->SetName("G");
	auto G_text = G->AddComponent<TextRendererComponent>();
	auto G_transfrom = G->GetComponent<TransformComponent>();
	G_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	G_transfrom->SetPosition(D3DXVECTOR3(280.0f, 270.0f, 0.0f));
	G->AddComponent<ColliderComponent>();
	G_text->AddText("Base", "G", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto H = board_layer->CreateActor();
	H->SetName("H");
	auto H_text = H->AddComponent<TextRendererComponent>();
	auto H_transfrom = H->GetComponent<TransformComponent>();
	H_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	H_transfrom->SetPosition(D3DXVECTOR3(310.0f, 270.0f, 0.0f));
	H->AddComponent<ColliderComponent>();
	H_text->AddText("Base", "H", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto I = board_layer->CreateActor();	
	I->SetName("I");
	auto I_text = I->AddComponent<TextRendererComponent>();	
	auto I_transfrom = I->GetComponent<TransformComponent>();
	I_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	I_transfrom->SetPosition(D3DXVECTOR3(340.0f, 270.0f, 0.0f));
	I->AddComponent<ColliderComponent>();
	I_text->AddText("Base", "I", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto J = board_layer->CreateActor();
	J->SetName("J");
	auto J_text = J->AddComponent<TextRendererComponent>();
	auto J_transfrom = J->GetComponent<TransformComponent>();
	J_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	J_transfrom->SetPosition(D3DXVECTOR3(370.0f, 270.0f, 0.0f));
	J->AddComponent<ColliderComponent>();
	J_text->AddText("Base", "J", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto K = board_layer->CreateActor();
	K->SetName("K");
	auto K_text = K->AddComponent<TextRendererComponent>();
	auto K_transfrom = K->GetComponent<TransformComponent>();
	K_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	K_transfrom->SetPosition(D3DXVECTOR3(100.0f, 310.0f, 0.0f));
	K->AddComponent<ColliderComponent>();
	K_text->AddText("Base", "K", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto L = board_layer->CreateActor();
	L->SetName("L");
	auto L_text = L->AddComponent<TextRendererComponent>();
	auto L_transfrom = L->GetComponent<TransformComponent>();
	L_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	L_transfrom->SetPosition(D3DXVECTOR3(130.0f, 310.0f, 0.0f));
	L->AddComponent<ColliderComponent>();
	L_text->AddText("Base", "L", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto M = board_layer->CreateActor();
	M->SetName("M");
	auto M_text = M->AddComponent<TextRendererComponent>();
	auto M_transfrom = M->GetComponent<TransformComponent>();
	M_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	M_transfrom->SetPosition(D3DXVECTOR3(160.0f, 310.0f, 0.0f));
	M->AddComponent<ColliderComponent>();
	M_text->AddText("Base", "M", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto N = board_layer->CreateActor();	
	N->SetName("N");
	auto N_text = N->AddComponent<TextRendererComponent>();
	auto N_transfrom = N->GetComponent<TransformComponent>();
	N_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	N_transfrom->SetPosition(D3DXVECTOR3(190.0f, 310.0f, 0.0f));
	N->AddComponent<ColliderComponent>();
	N_text->AddText("Base", "N", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto O = board_layer->CreateActor();
	O->SetName("O");
	auto O_text = O->AddComponent<TextRendererComponent>();
	auto O_transfrom = O->GetComponent<TransformComponent>();
	O_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	O_transfrom->SetPosition(D3DXVECTOR3(220.0f, 310.0f, 0.0f));
	O->AddComponent<ColliderComponent>();
	O_text->AddText("Base", "O", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto P = board_layer->CreateActor();	
	P->SetName("P");
	auto P_text = P->AddComponent<TextRendererComponent>();
	auto P_transfrom = P->GetComponent<TransformComponent>();
	P_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	P_transfrom->SetPosition(D3DXVECTOR3(250.0f, 310.0f, 0.0f));
	P->AddComponent<ColliderComponent>();
	P_text->AddText("Base", "P", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto Q = board_layer->CreateActor();	
	Q->SetName("Q");
	auto Q_text = Q->AddComponent<TextRendererComponent>();
	auto Q_transfrom = Q->GetComponent<TransformComponent>();
	Q_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	Q_transfrom->SetPosition(D3DXVECTOR3(280.0f, 310.0f, 0.0f));
	Q->AddComponent<ColliderComponent>();
	Q_text->AddText("Base", "Q", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto R = board_layer->CreateActor();
	R->SetName("R");
	auto R_text = R->AddComponent<TextRendererComponent>();
	auto R_transfrom = R->GetComponent<TransformComponent>();
	R_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	R_transfrom->SetPosition(D3DXVECTOR3(310.0f, 310.0f, 0.0f));
	R->AddComponent<ColliderComponent>();
	R_text->AddText("Base", "R", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto S = board_layer->CreateActor();
	S->SetName("S");
	auto S_text = S->AddComponent<TextRendererComponent>();
	auto S_transfrom = S->GetComponent<TransformComponent>();
	S_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	S_transfrom->SetPosition(D3DXVECTOR3(340.0f, 310.0f, 0.0f));
	S->AddComponent<ColliderComponent>();
	S_text->AddText("Base", "S", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto T = board_layer->CreateActor();
	T->SetName("T");
	auto T_text = T->AddComponent<TextRendererComponent>();
	auto T_transfrom = T->GetComponent<TransformComponent>();
	T_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	T_transfrom->SetPosition(D3DXVECTOR3(370.0f, 310.0f, 0.0f));
	T->AddComponent<ColliderComponent>();
	T_text->AddText("Base", "T", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto U = board_layer->CreateActor();
	U->SetName("U");
	auto U_text = U->AddComponent<TextRendererComponent>();
	auto U_transfrom = U->GetComponent<TransformComponent>();
	U_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	U_transfrom->SetPosition(D3DXVECTOR3(100.0f, 350.0f, 0.0f));
	U->AddComponent<ColliderComponent>();
	U_text->AddText("Base", "U", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto V = board_layer->CreateActor();
	V->SetName("V");
	auto V_text = V->AddComponent<TextRendererComponent>();
	auto V_transfrom = V->GetComponent<TransformComponent>();
	V_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	V_transfrom->SetPosition(D3DXVECTOR3(130.0f, 350.0f, 0.0f));
	V->AddComponent<ColliderComponent>();
	V_text->AddText("Base", "V", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto W = board_layer->CreateActor();
	W->SetName("W");
	auto W_text = W->AddComponent<TextRendererComponent>();
	auto W_transfrom = W->GetComponent<TransformComponent>();
	W_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	W_transfrom->SetPosition(D3DXVECTOR3(160.0f, 350.0f, 0.0f));
	W->AddComponent<ColliderComponent>();
	W_text->AddText("Base", "W", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto X = board_layer->CreateActor();
	X->SetName("X");
	auto X_text = X->AddComponent<TextRendererComponent>();
	auto X_transfrom = X->GetComponent<TransformComponent>();
	X_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	X_transfrom->SetPosition(D3DXVECTOR3(190.0f, 350.0f, 0.0f));
	X->AddComponent<ColliderComponent>();
	X_text->AddText("Base", "X", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto Y = board_layer->CreateActor();
	Y->SetName("Y");
	auto Y_text = Y->AddComponent<TextRendererComponent>();
	auto Y_transfrom = Y->GetComponent<TransformComponent>();
	Y_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	Y_transfrom->SetPosition(D3DXVECTOR3(220.0f, 350.0f, 0.0f));
	Y->AddComponent<ColliderComponent>();
	Y_text->AddText("Base", "Y", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto Z = board_layer->CreateActor();
	Z->SetName("Z");
	auto Z_text = Z->AddComponent<TextRendererComponent>();
	auto Z_transfrom = Z->GetComponent<TransformComponent>();
	Z_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	Z_transfrom->SetPosition(D3DXVECTOR3(250.0f, 350.0f, 0.0f));
	Z->AddComponent<ColliderComponent>();
	Z_text->AddText("Base", "Z", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	auto minus = board_layer->CreateActor();
	minus->SetName("-");
	auto minus_text = minus->AddComponent<TextRendererComponent>();
	auto minus_transfrom = minus->GetComponent<TransformComponent>();
	minus_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	minus_transfrom->SetPosition(D3DXVECTOR3(280.0f, 350.0f, 0.0f));
	minus->AddComponent<ColliderComponent>();
	minus_text->AddText("Base", "-", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	auto period = board_layer->CreateActor();
	period->SetName(".");
	auto period_text = period->AddComponent<TextRendererComponent>();
	auto period_transfrom = period ->GetComponent<TransformComponent>();
	period_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	period_transfrom->SetPosition(D3DXVECTOR3(310.0f, 350.0f, 0.0f));
	period->AddComponent<ColliderComponent>();
	period_text->AddText("Base", ".", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	auto comma = board_layer->CreateActor();
	comma->SetName(",");
	auto comma_text = comma->AddComponent<TextRendererComponent>();
	auto comma_transfrom = comma->GetComponent<TransformComponent>();
	comma_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	comma_transfrom->SetPosition(D3DXVECTOR3(340.0f, 350.0f, 0.0f));
	comma->AddComponent<ColliderComponent>();
	comma_text->AddText("Base", ",", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto zero = board_layer->CreateActor();
	zero->SetName("0");
	auto zero_text = zero->AddComponent<TextRendererComponent>();
	auto zero_transfrom = zero->GetComponent<TransformComponent>();
	zero_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	zero_transfrom->SetPosition(D3DXVECTOR3(220.0f, 390.0f, 0.0f));
	zero->AddComponent<ColliderComponent>();
	zero_text->AddText("Base", "0", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto one = board_layer->CreateActor();
	one->SetName("1");
	auto one_text = one->AddComponent<TextRendererComponent>();
	auto one_transfrom = one->GetComponent<TransformComponent>();
	one_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	one_transfrom->SetPosition(D3DXVECTOR3(250.0f, 390.0f, 0.0f));
	one->AddComponent<ColliderComponent>();
	one_text->AddText("Base", "1", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto two = board_layer->CreateActor();
	two->SetName("2");
	auto two_text = two->AddComponent<TextRendererComponent>();
	auto two_transfrom = two->GetComponent<TransformComponent>();
	two_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	two_transfrom->SetPosition(D3DXVECTOR3(280.0f, 390.0f, 0.0f));
	two->AddComponent<ColliderComponent>();
	two_text->AddText("Base", "2", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto three = board_layer->CreateActor();
	three->SetName("3");
	auto three_text = three->AddComponent<TextRendererComponent>();
	auto three_transfrom = three->GetComponent<TransformComponent>();
	three_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	three_transfrom->SetPosition(D3DXVECTOR3(310.0f, 390.0f, 0.0f));
	three->AddComponent<ColliderComponent>();
	three_text->AddText("Base", "3", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto four = board_layer->CreateActor();
	four->SetName("4");
	auto four_text = four->AddComponent<TextRendererComponent>();
	auto four_transfrom = four->GetComponent<TransformComponent>();
	four_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	four_transfrom->SetPosition(D3DXVECTOR3(340.0f, 390.0f, 0.0f));
	four->AddComponent<ColliderComponent>();
	four_text->AddText("Base", "4", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto five = board_layer->CreateActor();
	five->SetName("5");
	auto five_text = five->AddComponent<TextRendererComponent>();
	auto five_transfrom = five->GetComponent<TransformComponent>();
	five_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	five_transfrom->SetPosition(D3DXVECTOR3(500.0f, 270.0f, 0.0f));
	five->AddComponent<ColliderComponent>();
	five_text->AddText("Base", "5", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto six = board_layer->CreateActor();
	six->SetName("6");
	auto six_text = six->AddComponent<TextRendererComponent>();
	auto six_transfrom = six->GetComponent<TransformComponent>();
	six_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	six_transfrom->SetPosition(D3DXVECTOR3(530.0f, 270.0f, 0.0f));
	six->AddComponent<ColliderComponent>();
	six_text->AddText("Base", "6", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto seven = board_layer->CreateActor();
	U->SetName("U");
	auto seven_text = seven->AddComponent<TextRendererComponent>();
	auto seven_transfrom = seven->GetComponent<TransformComponent>();
	seven_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	seven_transfrom->SetPosition(D3DXVECTOR3(560.0f, 270.0f, 0.0f));
	seven->AddComponent<ColliderComponent>();
	seven_text->AddText("Base", "7", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto eight = board_layer->CreateActor();
	eight->SetName("8");
	auto eight_text = eight->AddComponent<TextRendererComponent>();
	auto eight_transfrom = eight->GetComponent<TransformComponent>();
	eight_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	eight_transfrom->SetPosition(D3DXVECTOR3(590.0f, 270.0f, 0.0f));
	eight->AddComponent<ColliderComponent>();
	eight_text->AddText("Base", "8", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto nine = board_layer->CreateActor();
	nine->SetName("9");
	auto nine_text = nine->AddComponent<TextRendererComponent>();
	auto nine_transfrom = nine->GetComponent<TransformComponent>();
	nine_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	nine_transfrom->SetPosition(D3DXVECTOR3(620.0f, 270.0f, 0.0f));
	nine->AddComponent<ColliderComponent>();
	nine_text->AddText("Base", "9", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto excharm = board_layer->CreateActor();
	excharm->SetName("!");
	auto excharm_text = excharm->AddComponent<TextRendererComponent>();
	auto excharm_transfrom = excharm->GetComponent<TransformComponent>();
	excharm_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	excharm_transfrom->SetPosition(D3DXVECTOR3(500.0f, 310.0f, 0.0f));
	excharm->AddComponent<ColliderComponent>();
	excharm_text->AddText("Base", "!", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto question = board_layer->CreateActor();
	question->SetName("?");
	auto question_text = question->AddComponent<TextRendererComponent>();
	auto question_transfrom = question->GetComponent<TransformComponent>();
	question_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	question_transfrom->SetPosition(D3DXVECTOR3(530.0f, 310.0f, 0.0f));
	question->AddComponent<ColliderComponent>();
	question_text->AddText("Base", "?", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto left = board_layer->CreateActor();
	left->SetName("(");
	auto left_text = left->AddComponent<TextRendererComponent>();
	auto left_transfrom = left->GetComponent<TransformComponent>();
	left_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	left_transfrom->SetPosition(D3DXVECTOR3(560.0f, 310.0f, 0.0f));
	left->AddComponent<ColliderComponent>();
	left_text->AddText("Base", "(", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto right = board_layer->CreateActor();
	right->SetName(")");
	auto right_text = right->AddComponent<TextRendererComponent>();
	auto right_transfrom = right->GetComponent<TransformComponent>();
	right_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	right_transfrom->SetPosition(D3DXVECTOR3(590.0f, 310.0f, 0.0f));
	right->AddComponent<ColliderComponent>();
	right_text->AddText("Base", ")", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto a = board_layer->CreateActor();
	a->SetName("a");
	auto a_text = a->AddComponent<TextRendererComponent>();
	auto a_transfrom = a->GetComponent<TransformComponent>();
	a_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	a_transfrom->SetPosition(D3DXVECTOR3(500.0f, 350.0f, 0.0f));
	a->AddComponent<ColliderComponent>();
	a_text->AddText("Base", "a", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto b = board_layer->CreateActor();
	b->SetName("b");
	auto b_text = b->AddComponent<TextRendererComponent>();
	auto b_transfrom = b->GetComponent<TransformComponent>();
	b_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	b_transfrom->SetPosition(D3DXVECTOR3(530.0f, 350.0f, 0.0f));
	b->AddComponent<ColliderComponent>();
	b_text->AddText("Base", "b", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto c = board_layer->CreateActor();
	c->SetName("c");
	auto c_text = c->AddComponent<TextRendererComponent>();
	auto c_transfrom = c->GetComponent<TransformComponent>();
	c_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	c_transfrom->SetPosition(D3DXVECTOR3(560.0f, 350.0f, 0.0f));
	c->AddComponent<ColliderComponent>();
	c_text->AddText("Base", "c", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto d = board_layer->CreateActor();
	d->SetName("d");
	auto d_text = d->AddComponent<TextRendererComponent>();
	auto d_transfrom = d->GetComponent<TransformComponent>();
	d_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	d_transfrom->SetPosition(D3DXVECTOR3(590.0f, 350.0f, 0.0f));
	d->AddComponent<ColliderComponent>();
	d_text->AddText("Base", "d", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto e = board_layer->CreateActor();
	e->SetName("e");
	auto e_text = e->AddComponent<TextRendererComponent>();
	auto e_transfrom = e->GetComponent<TransformComponent>();
	e_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	e_transfrom->SetPosition(D3DXVECTOR3(620.0f, 350.0f, 0.0f));
	e->AddComponent<ColliderComponent>();
	e_text->AddText("Base", "e", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto f = board_layer->CreateActor();
	f->SetName("f");
	auto f_text = f->AddComponent<TextRendererComponent>();
	auto f_transfrom = f->GetComponent<TransformComponent>();
	f_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	f_transfrom->SetPosition(D3DXVECTOR3(650.0f, 350.0f, 0.0f));
	f->AddComponent<ColliderComponent>();
	f_text->AddText("Base", "f", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto g = board_layer->CreateActor();
	g->SetName("g");
	auto g_text = g->AddComponent<TextRendererComponent>();
	auto g_transfrom = g->GetComponent<TransformComponent>();
	g_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	g_transfrom->SetPosition(D3DXVECTOR3(680.0f, 350.0f, 0.0f));
	g->AddComponent<ColliderComponent>();
	g_text->AddText("Base", "g", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto h = board_layer->CreateActor();
	h->SetName("h");
	auto h_text = h->AddComponent<TextRendererComponent>();
	auto h_transfrom = h->GetComponent<TransformComponent>();
	h_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	h_transfrom->SetPosition(D3DXVECTOR3(710.0f, 350.0f, 0.0f));
	h->AddComponent<ColliderComponent>();
	h_text->AddText("Base", "h", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto i = board_layer->CreateActor();
	i->SetName("i");
	auto i_text = i->AddComponent<TextRendererComponent>();
	auto i_transfrom = i->GetComponent<TransformComponent>();
	i_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	i_transfrom->SetPosition(D3DXVECTOR3(740.0f, 350.0f, 0.0f));
	i->AddComponent<ColliderComponent>();
	i_text->AddText("Base", "i", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto j = board_layer->CreateActor();
	j->SetName("j");
	auto j_text = j->AddComponent<TextRendererComponent>();
	auto j_transfrom = j->GetComponent<TransformComponent>();
	j_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	j_transfrom->SetPosition(D3DXVECTOR3(770.0f, 350.0f, 0.0f));
	j->AddComponent<ColliderComponent>();
	j_text->AddText("Base", "j", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto k = board_layer->CreateActor();
	k->SetName("k");
	auto k_text = k->AddComponent<TextRendererComponent>();
	auto k_transfrom = k->GetComponent<TransformComponent>();
	k_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	k_transfrom->SetPosition(D3DXVECTOR3(500.0f, 390.0f, 0.0f));
	k->AddComponent<ColliderComponent>();
	k_text->AddText("Base", "k", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto l = board_layer->CreateActor();
	l->SetName("l");
	auto l_text = l->AddComponent<TextRendererComponent>();
	auto l_transfrom = l->GetComponent<TransformComponent>();
	l_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	l_transfrom->SetPosition(D3DXVECTOR3(530.0f, 390.0f, 0.0f));
	l->AddComponent<ColliderComponent>();
	l_text->AddText("Base", "l", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto m = board_layer->CreateActor();
	m->SetName("m");
	auto m_text = m->AddComponent<TextRendererComponent>();
	auto m_transfrom = m->GetComponent<TransformComponent>();
	m_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	m_transfrom->SetPosition(D3DXVECTOR3(560.0f, 390.0f, 0.0f));
	m->AddComponent<ColliderComponent>();
	m_text->AddText("Base", "m", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto n = board_layer->CreateActor();
	n->SetName("n");
	auto n_text = n->AddComponent<TextRendererComponent>();
	auto n_transfrom = n->GetComponent<TransformComponent>();
	n_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	n_transfrom->SetPosition(D3DXVECTOR3(590.0f, 390.0f, 0.0f));
	n->AddComponent<ColliderComponent>();
	n_text->AddText("Base", "n", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto o = board_layer->CreateActor();
	o->SetName("o");
	auto o_text = o->AddComponent<TextRendererComponent>();
	auto o_transfrom = o->GetComponent<TransformComponent>();
	o_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	o_transfrom->SetPosition(D3DXVECTOR3(620.0f, 390.0f, 0.0f));
	o->AddComponent<ColliderComponent>();
	o_text->AddText("Base", "o", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto p = board_layer->CreateActor();
	p->SetName("p");
	auto p_text = p->AddComponent<TextRendererComponent>();
	auto p_transfrom = p->GetComponent<TransformComponent>();
	p_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	p_transfrom->SetPosition(D3DXVECTOR3(650.0f, 390.0f, 0.0f));
	p->AddComponent<ColliderComponent>();
	p_text->AddText("Base", "p", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto q = board_layer->CreateActor();
	q->SetName("q");
	auto q_text = q->AddComponent<TextRendererComponent>();
	auto q_transfrom = q->GetComponent<TransformComponent>();
	q_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	q_transfrom->SetPosition(D3DXVECTOR3(680.0f, 390.0f, 0.0f));
	q->AddComponent<ColliderComponent>();
	q_text->AddText("Base", "q", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto r = board_layer->CreateActor();
	r->SetName("r");
	auto r_text = r->AddComponent<TextRendererComponent>();
	auto r_transfrom = r->GetComponent<TransformComponent>();
	r_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	r_transfrom->SetPosition(D3DXVECTOR3(710.0f, 390.0f, 0.0f));
	r->AddComponent<ColliderComponent>();
	r_text->AddText("Base", "r", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto s = board_layer->CreateActor();
	s->SetName("s");
	auto s_text = s->AddComponent<TextRendererComponent>();
	auto s_transfrom = s->GetComponent<TransformComponent>();
	s_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	s_transfrom->SetPosition(D3DXVECTOR3(740.0f, 390.0f, 0.0f));
	s->AddComponent<ColliderComponent>();
	s_text->AddText("Base", "s", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto t = board_layer->CreateActor();
	t->SetName("t");
	auto t_text = t->AddComponent<TextRendererComponent>();
	auto t_transfrom = t->GetComponent<TransformComponent>();
	t_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	t_transfrom->SetPosition(D3DXVECTOR3(770.0f, 390.0f, 0.0f));
	t->AddComponent<ColliderComponent>();
	t_text->AddText("Base", "t", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto u = board_layer->CreateActor();
	u->SetName("u");
	auto u_text = u->AddComponent<TextRendererComponent>();
	auto u_transfrom = u->GetComponent<TransformComponent>();
	u_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	u_transfrom->SetPosition(D3DXVECTOR3(900.0f, 270.0f, 0.0f));
	u->AddComponent<ColliderComponent>();
	u_text->AddText("Base", "u", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto v = board_layer->CreateActor();
	v->SetName("v");
	auto v_text = v->AddComponent<TextRendererComponent>();
	auto v_transfrom = v->GetComponent<TransformComponent>();
	v_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	v_transfrom->SetPosition(D3DXVECTOR3(930.0f, 270.0f, 0.0f));
	v->AddComponent<ColliderComponent>();
	v_text->AddText("Base", "v", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto w = board_layer->CreateActor();
	w->SetName("w");
	auto w_text = w->AddComponent<TextRendererComponent>();
	auto w_transfrom = w->GetComponent<TransformComponent>();
	w_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	w_transfrom->SetPosition(D3DXVECTOR3(960.0f, 270.0f, 0.0f));
	w->AddComponent<ColliderComponent>();
	w_text->AddText("Base", "w", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto x = board_layer->CreateActor();
	x->SetName("x");
	auto x_text = x->AddComponent<TextRendererComponent>();
	auto x_transfrom = x->GetComponent<TransformComponent>();
	x_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	x_transfrom->SetPosition(D3DXVECTOR3(990.0f, 270.0f, 0.0f));
	x->AddComponent<ColliderComponent>();
	x_text->AddText("Base", "x", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto y = board_layer->CreateActor();
	y->SetName("y");
	auto y_text = y->AddComponent<TextRendererComponent>();
	auto y_transfrom = y->GetComponent<TransformComponent>();
	y_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	y_transfrom->SetPosition(D3DXVECTOR3(1020.0f, 270.0f, 0.0f));
	y->AddComponent<ColliderComponent>();
	y_text->AddText("Base", "y", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto z = board_layer->CreateActor();
	z->SetName("z");
	auto z_text = z->AddComponent<TextRendererComponent>();
	auto z_transfrom = z->GetComponent<TransformComponent>();
	z_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	z_transfrom->SetPosition(D3DXVECTOR3(1050.0f, 270.0f, 0.0f));
	z->AddComponent<ColliderComponent>();
	z_text->AddText("Base", "z", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto end = board_layer->CreateActor();
	end->SetName("End");
	auto end_text = end->AddComponent<TextRendererComponent>(); 
	auto end_transfrom = end->GetComponent<TransformComponent>();
	end_transfrom->SetScale(D3DXVECTOR3(80.0f, 45.0f, 1.0f));
	end_transfrom->SetPosition(D3DXVECTOR3(900.0f, 310.0f, 0.0f));
	end->AddComponent<ColliderComponent>();
	end_text->AddText("Base", "< END >", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//auto scope_layer = CreateLayer("Scope");
	scope = board_layer->CreateActor();
	scope->SetName("Scope");
	scope->SetUpdate(false);
	scope->AddComponent<ColliderComponent>()->SetOffsetPosition(D3DXVECTOR3(212.f, 0.0f ,0.0f));
	scope->AddComponent<MeshRendererComponent>();
	scope->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(1.91f, 2.0f, 1.0f));
	scope->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(50.0f, 350.0f, 0.0f));
	animator = scope->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Xml/Animation/Scope.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("Scope");

	/*
	BackGround
	*/

	auto back_layer = CreateLayer("Background");
	auto select_name = back_layer->CreateActor();
	select_name->SetName("NameSelectBackground");
	select_name->AddComponent<MeshRendererComponent>();
	select_name->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.0f, 2.3f, 1.0f));
	select_name->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	animator = select_name->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Xml/Animation/SelectName.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("NameSelectBackground");
}

NameSelectScene::~NameSelectScene()
{
}

void NameSelectScene::Initialize()
{
	Scene::Initialize();

	graphics->SetBackClearColor(0x000000);
}

void NameSelectScene::Input()
{
	frame_counter += timer->GetDeltaTimeSec();
	frame_counter_text += timer->GetDeltaTimeSec();
	auto scope_transform = scope->GetComponent<TransformComponent>();
	auto scope_position = scope_transform->GetPosition();
	
	if (frame_counter > 0.05)
	{
		if (GetAsyncKeyState('A') & 0x8000)
		{
			board_layer->SetOffsetPosition(10.0f, 0.0f, 0.0f);
		}
		else if (GetAsyncKeyState('D') & 0x8000)
		{
			board_layer->SetOffsetPosition(-10.0f, 0.0f, 0.0f);
		}
	
		if ((GetAsyncKeyState('W') & 0x8000) && scope_position.y > 275.0f)
		{
			scope_position.y -= 3;
		}
		else if ((GetAsyncKeyState('S') & 0x8000) && scope_position.y < 450.0f)
		{
			scope_position.y += 3;
		}

		if (GetAsyncKeyState('X') & 0x8000)
		{
			auto collider = scope->GetComponent<ColliderComponent>();
			auto text_renderer = select->GetComponent<TextRendererComponent>();

			if (auto actor = collider->GetOverlapActor("End"))
			{
				auto scene_manager = tool->GetManager<SubsystemManager>()->GetSubsystem<SceneManager>();
				scene_manager->SetCurrentScene("InGame");
			}

			auto actor = collider->GetOverlapActor_back();
			if (actor && static_cast<uint>(player_name.size()) < name_size 
				&& frame_counter_text > 0.5)
			{
				auto name = text_renderer->GetText("Base");
				player_name = name->text + actor->GetName();
				name->text = player_name;

				frame_counter_text = 0.0f;
			}
		}
		scope_transform->SetPosition(scope_position);
		frame_counter = 0.0f;
	}
}

void NameSelectScene::Update()
{
	Input();
	Scene::Update();
}

void NameSelectScene::Destroy()
{
	Scene::Destroy();
}
