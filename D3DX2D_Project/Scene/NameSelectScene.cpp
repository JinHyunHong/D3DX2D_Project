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
	animator->AddAnimation("Assets/Animation/RegisterName.xml");
	animator->SetAnimationMode(AnimationMode::Play);
	animator->SetCurrentAnimation("RegisterName");

	/*
		Selected_text
	*/
	select = text_layer->CreateActor();
	auto select_text = select->AddComponent<TextRendererComponent>();
	auto select_transfrom = select->GetComponent<TransformComponent>();
	select_transfrom->SetPosition(D3DXVECTOR3(85.0f, 205.0f, 0.0f));
	select_text->AddText(" ", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

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
	A_text->AddText("A", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	A->AddComponent<ColliderComponent>();

	auto B = board_layer->CreateActor();
	B->SetName("B");
	auto B_text = B->AddComponent<TextRendererComponent>();
	auto B_transfrom = B->GetComponent<TransformComponent>();
	B_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	B_transfrom->SetPosition(D3DXVECTOR3(130.0f, 270.0f, 0.0f));
	B_text->AddText("B", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	B->AddComponent<ColliderComponent>();

	auto C = board_layer->CreateActor();
	C->SetName("C");
	auto C_transfrom = C->GetComponent<TransformComponent>();
	C_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	C_transfrom->SetPosition(D3DXVECTOR3(160.0f, 270.0f, 0.0f));
	auto C_text = C->AddComponent<TextRendererComponent>();
	C_text->AddText("C", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	C->AddComponent<ColliderComponent>();

	auto D = board_layer->CreateActor();
	auto D_text = D->AddComponent<TextRendererComponent>(); 
	auto D_transfrom = D->GetComponent<TransformComponent>();
	D_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	D_transfrom->SetPosition(D3DXVECTOR3(190.0f, 270.0f, 0.0f));
	D->AddComponent<ColliderComponent>();
	D_text->AddText("D", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	auto E = board_layer->CreateActor();
	E->SetName("E");
	auto E_text = E->AddComponent<TextRendererComponent>();
	auto E_transfrom = E->GetComponent<TransformComponent>();
	E_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	E_transfrom->SetPosition(D3DXVECTOR3(220.0f, 270.0f, 0.0f));
	E->AddComponent<ColliderComponent>();
	E_text->AddText("E", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	
	auto F = board_layer->CreateActor();
	F->SetName("F");
	auto F_text = F->AddComponent<TextRendererComponent>();
	auto F_transfrom = F->GetComponent<TransformComponent>();
	F_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	F_transfrom->SetPosition(D3DXVECTOR3(250.0f, 270.0f, 0.0f));
	F->AddComponent<ColliderComponent>();
	F_text->AddText("F", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto G = board_layer->CreateActor();
	auto G_text = G->AddComponent<TextRendererComponent>();
	auto G_transfrom = G->GetComponent<TransformComponent>();
	G_transfrom->SetScale(D3DXVECTOR3(30.0f, 30.0f, 1.0f));
	G_transfrom->SetPosition(D3DXVECTOR3(280.0f, 270.0f, 0.0f));
	G->AddComponent<ColliderComponent>();
	G_text->AddText("G", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	auto H = board_layer->CreateActor();
	auto H_text = H->AddComponent<TextRendererComponent>();
	H_text->AddText("H", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(310.0f, 270.0f));

	auto I = board_layer->CreateActor();
	auto I_text = I->AddComponent<TextRendererComponent>();
	I_text->AddText("I", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(340.0f, 270.0f));

	auto J = board_layer->CreateActor();
	auto J_text = J->AddComponent<TextRendererComponent>();
	J_text->AddText("J", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(370.0f, 270.0f));

	auto K = board_layer->CreateActor();
	auto K_text = K->AddComponent<TextRendererComponent>();
	K_text->AddText("K", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(100.0f, 310.0f));

	auto L = board_layer->CreateActor();
	auto L_text = L->AddComponent<TextRendererComponent>();
	L_text->AddText("L", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(130.0f, 310.0f));

	auto M = board_layer->CreateActor();
	auto M_text = M->AddComponent<TextRendererComponent>();
	M_text->AddText("M", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(160.0f, 310.0f));

	auto N = board_layer->CreateActor();
	auto N_text = N->AddComponent<TextRendererComponent>();
	N_text->AddText("N", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(190.0f, 310.0f));

	auto O = board_layer->CreateActor();
	auto O_text = O->AddComponent<TextRendererComponent>();
	O_text->AddText("O", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(220.0f, 310.0f));

	auto P = board_layer->CreateActor();
	auto P_text = P->AddComponent<TextRendererComponent>();
	P_text->AddText("P", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(250.0f, 310.0f));

	auto Q = board_layer->CreateActor();
	auto Q_text = Q->AddComponent<TextRendererComponent>();
	Q_text->AddText("Q", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(280.0f, 310.0f));

	auto R = board_layer->CreateActor();
	auto R_text = R->AddComponent<TextRendererComponent>();
	R_text->AddText("R", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(310.0f, 310.0f));

	auto S = board_layer->CreateActor();
	auto S_text = S->AddComponent<TextRendererComponent>();
	S_text->AddText("S", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(340.0f, 310.0f));

	auto T = board_layer->CreateActor();
	auto T_text = T->AddComponent<TextRendererComponent>();
	T_text->AddText("T", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(370.0f, 310.0f));

	auto U = board_layer->CreateActor();
	auto U_text = U->AddComponent<TextRendererComponent>();
	U_text->AddText("U", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(100.0f, 350.0f));

	auto V = board_layer->CreateActor();
	auto V_text = V->AddComponent<TextRendererComponent>();
	V_text->AddText("V", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(130.0f, 350.0f));

	auto W = board_layer->CreateActor();
	auto W_text = W->AddComponent<TextRendererComponent>();
	W_text->AddText("W", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(160.0f, 350.0f));

	auto X = board_layer->CreateActor();
	auto X_text = X->AddComponent<TextRendererComponent>();
	X_text->AddText("X", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(190.0f, 350.0f));

	auto Y = board_layer->CreateActor();
	auto Y_text = Y->AddComponent<TextRendererComponent>();
	Y_text->AddText("Y", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(220.0f, 350.0f));

	auto Z = board_layer->CreateActor();
	auto Z_text = Z->AddComponent<TextRendererComponent>();
	Z_text->AddText("Z", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(250.0f, 350.0f));
	
	auto minus = board_layer->CreateActor();
	auto minus_text = minus->AddComponent<TextRendererComponent>();
	minus_text->AddText("-", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(280.0f, 350.0f));
	
	auto period = board_layer->CreateActor();
	auto period_text = period->AddComponent<TextRendererComponent>();
	period_text->AddText(".", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(310.0f, 350.0f));
	
	auto comma = board_layer->CreateActor();
	auto comma_text = comma->AddComponent<TextRendererComponent>();
	comma_text->AddText(",", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(340.0f, 350.0f));

	auto zero = board_layer->CreateActor();
	auto zero_text = zero->AddComponent<TextRendererComponent>();
	zero_text->AddText("0", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(220.0f, 390.0f));

	auto one = board_layer->CreateActor();
	auto one_text = one->AddComponent<TextRendererComponent>();
	one_text->AddText("1", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(250.0f, 390.0f));

	auto two = board_layer->CreateActor();
	auto two_text = two->AddComponent<TextRendererComponent>();
	two_text->AddText("2", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(280.0f, 390.0f));

	auto three = board_layer->CreateActor();
	auto three_text = three->AddComponent<TextRendererComponent>();
	three_text->AddText("3", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(310.0f, 390.0f));

	auto four = board_layer->CreateActor();
	auto four_text = four->AddComponent<TextRendererComponent>();
	four_text->AddText("4", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(340.0f, 390.0f));

	auto five = board_layer->CreateActor();
	auto five_text = five->AddComponent<TextRendererComponent>();
	five_text->AddText("5", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(500.0f, 270.0f));

	auto six = board_layer->CreateActor();
	auto six_text = six->AddComponent<TextRendererComponent>();
	six_text->AddText("6", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(530.0f, 270.0f));

	auto seven = board_layer->CreateActor();
	auto seven_text = seven->AddComponent<TextRendererComponent>();
	seven_text->AddText("7", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(560.0f, 270.0f));

	auto eight = board_layer->CreateActor();
	auto eight_text = eight->AddComponent<TextRendererComponent>();
	eight_text->AddText("8", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(590.0f, 270.0f));

	auto nine = board_layer->CreateActor();
	auto nine_text = nine->AddComponent<TextRendererComponent>();
	nine_text->AddText("9", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(620.0f, 270.0f));

	auto excharm = board_layer->CreateActor();
	auto excharm_text = excharm->AddComponent<TextRendererComponent>();
	excharm_text->AddText("!", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(500.0f, 310.0f));

	auto question = board_layer->CreateActor();
	auto question_text = question->AddComponent<TextRendererComponent>();
	question_text->AddText("?", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(530.0f, 310.0f));

	auto left = board_layer->CreateActor();
	auto left_text = left->AddComponent<TextRendererComponent>();
	left_text->AddText("(", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(560.0f, 310.0f));

	auto right = board_layer->CreateActor();
	auto right_text = right->AddComponent<TextRendererComponent>();
	right_text->AddText(")", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(590.0f, 310.0f));

	auto a = board_layer->CreateActor();
	auto a_text = a->AddComponent<TextRendererComponent>();
	a_text->AddText("a", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(500.0f, 350.0f));

	auto b = board_layer->CreateActor();
	auto b_text = b->AddComponent<TextRendererComponent>();
	b_text->AddText("b", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(530.0f, 350.0f));

	auto c = board_layer->CreateActor();
	auto c_text = c->AddComponent<TextRendererComponent>();
	c_text->AddText("c", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(560.0f, 350.0f));

	auto d = board_layer->CreateActor();
	auto d_text = d->AddComponent<TextRendererComponent>();
	d_text->AddText("d", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(590.0f, 350.0f));

	auto e = board_layer->CreateActor();
	auto e_text = e->AddComponent<TextRendererComponent>();
	e_text->AddText("e", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(620.0f, 350.0f));

	auto f = board_layer->CreateActor();
	auto f_text = f->AddComponent<TextRendererComponent>();
	f_text->AddText("f", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(650.0f, 350.0f));

	auto g = board_layer->CreateActor();
	auto g_text = g->AddComponent<TextRendererComponent>();
	g_text->AddText("g", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(680.0f, 350.0f));

	auto h = board_layer->CreateActor();
	auto h_text = h->AddComponent<TextRendererComponent>();
	h_text->AddText("h", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(710.0f, 350.0f));

	auto i = board_layer->CreateActor();
	auto i_text = i->AddComponent<TextRendererComponent>();
	i_text->AddText("i", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(740.0f, 350.0f));

	auto j = board_layer->CreateActor();
	auto j_text = j->AddComponent<TextRendererComponent>();
	j_text->AddText("j", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(770.0f, 350.0f));

	auto k = board_layer->CreateActor();
	auto k_text = k->AddComponent<TextRendererComponent>();
	k_text->AddText("k", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(500.0f, 390.0f));

	auto l = board_layer->CreateActor();
	auto l_text = l->AddComponent<TextRendererComponent>();
	l_text->AddText("l", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(530.0f, 390.0f));

	auto m = board_layer->CreateActor();
	auto m_text = m->AddComponent<TextRendererComponent>();
	m_text->AddText("m", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(560.0f, 390.0f));

	auto n = board_layer->CreateActor();
	auto n_text = n->AddComponent<TextRendererComponent>();
	n_text->AddText("n", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(590.0f, 390.0f));

	auto o = board_layer->CreateActor();
	auto o_text = o->AddComponent<TextRendererComponent>();
	o_text->AddText("o", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(620.0f, 390.0f));

	auto p = board_layer->CreateActor();
	auto p_text = p->AddComponent<TextRendererComponent>();
	p_text->AddText("p", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(650.0f, 390.0f));

	auto q = board_layer->CreateActor();
	auto q_text = q->AddComponent<TextRendererComponent>();
	q_text->AddText("q", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(680.0f, 390.0f));

	auto r = board_layer->CreateActor();
	auto r_text = r->AddComponent<TextRendererComponent>();
	r_text->AddText("r", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(710.0f, 390.0f));

	auto s = board_layer->CreateActor();
	auto s_text = s->AddComponent<TextRendererComponent>();
	s_text->AddText("s", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(740.0f, 390.0f));

	auto t = board_layer->CreateActor();
	auto t_text = t->AddComponent<TextRendererComponent>();
	t_text->AddText("t", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(770.0f, 390.0f));

	auto u = board_layer->CreateActor();
	auto u_text = u->AddComponent<TextRendererComponent>();
	u_text->AddText("u", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(900.0f, 270.0f));

	auto v = board_layer->CreateActor();
	auto v_text = v->AddComponent<TextRendererComponent>();
	v_text->AddText("v", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(930.0f, 270.0f));

	auto w = board_layer->CreateActor();
	auto w_text = w->AddComponent<TextRendererComponent>();
	w_text->AddText("w", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(960.0f, 270.0f));

	auto x = board_layer->CreateActor();
	auto x_text = x->AddComponent<TextRendererComponent>();
	x_text->AddText("x", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(990.0f, 270.0f));

	auto y = board_layer->CreateActor();
	auto y_text = y->AddComponent<TextRendererComponent>();
	y_text->AddText("y", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1020.0f, 270.0f));

	auto z = board_layer->CreateActor();
	auto z_text = z->AddComponent<TextRendererComponent>();
	z_text->AddText("z", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1050.0f, 270.0f));

	auto end = board_layer->CreateActor();
	end->SetName("End");
	auto end_text = end->AddComponent<TextRendererComponent>(); 
	auto end_transfrom = end->GetComponent<TransformComponent>();
	end_transfrom->SetScale(D3DXVECTOR3(80.0f, 45.0f, 1.0f));
	end_transfrom->SetPosition(D3DXVECTOR3(900.0f, 310.0f, 0.0f));
	end->AddComponent<ColliderComponent>();
	end_text->AddText("< END >", D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//auto scope_layer = CreateLayer("Scope");
	scope = board_layer->CreateActor();
	scope->SetName("Scope");
	scope->SetUpdate(false);
	scope->AddComponent<ColliderComponent>()->SetOffsetPosition(D3DXVECTOR3(212.f, 0.0f ,0.0f));
	scope->AddComponent<MeshRendererComponent>();
	scope->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(1.91f, 2.0f, 1.0f));
	scope->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(50.0f, 350.0f, 0.0f));
	animator = scope->AddComponent<AnimatorComponent>();
	animator->AddAnimation("Assets/Animation/Scope.xml");
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
	animator->AddAnimation("Assets/Animation/SelectName.xml");
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
			if (actor && static_cast<uint>(player_name.size()) < name_size)
			{
				auto name = text_renderer->GetText(player_name);
				player_name = name->text + actor->GetName();
				name->text = player_name;
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
