/*#include "testUI.h"


testUI::testUI(Game* game)
{
    m_game = game;

    // Create the label.
	m_label = sfg::Label::Create( "Hello world!" );

	// Create a simple button and connect the click signal.
	m_button = sfg::Button::Create( "Greet SFGUI!" );
	m_button->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &testUI::OnButtonClick, this ) );

	// Create a vertical box layouter with 5 pixels spacing and add the label
	// and button to it.
	m_box = sfg::Box::Create( sfg::Box::Orientation::VERTICAL, 5.0f );
	m_box->Pack( m_label );
	m_box->Pack( m_button, false );

	// Create a window and add the box layouter to it. Also set the window's title.
	m_window = sfg::Window::Create();
	m_window->SetTitle( "Hello world!" );
	m_window->Add( m_box );

	// Create a desktop and add the window to it.
    m_desktop.Add( m_window );
}

testUI::~testUI()
{
    //dtor
}

void testUI::OnButtonClick() {
	m_label->SetText( "Hello SFGUI, pleased to meet you!" );
}


void testUI::draw()
{
    m_sfgui.Display(m_game->m_window);
}
) */
