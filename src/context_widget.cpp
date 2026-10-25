#include "aiws/gui/context_widget.hpp"

#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>

namespace aiws::gui
{

    ContextWidget::ContextWidget(QWidget *parent) : QWidget(parent)
    {
        context_budget_slider_ = new QSlider(Qt::Horizontal, this);
        context_budget_slider_->setRange(1, 500);
        context_budget_slider_->setValue(300);

        budget_value_label_ = new QLabel("300", this);
        build_context_button_ = new QPushButton("Build Context", this);

        context_text_ = new QPlainTextEdit(this);
        context_text_->setPlaceholderText("Built context will appear here.");

        auto *Budget_Label = new QLabel("Token Budget:", this);

        auto *H_Layout_1 = new QHBoxLayout;
        H_Layout_1->addWidget(Budget_Label);
        H_Layout_1->addWidget(context_budget_slider_);
        H_Layout_1->addWidget(budget_value_label_);
        H_Layout_1->addWidget(build_context_button_);

        auto *Context_Label = new QLabel("Context", this);
        QFont ContextFont = Context_Label->font();
        ContextFont.setBold(true);
        Context_Label->setFont(ContextFont);

        auto *main_layout = new QVBoxLayout;
        main_layout->addWidget(Context_Label);
        main_layout->addLayout(H_Layout_1);
        main_layout->addWidget(context_text_);

        setLayout(main_layout);

        connect(build_context_button_, &QPushButton::clicked, this, &ContextWidget::request_context);

        connect(context_budget_slider_, &QSlider::valueChanged, this, &ContextWidget::budget_changed);
    }

    int ContextWidget::token_budget() const
    {
        // TODO
        return 0;
    }

    void ContextWidget::set_build_context_enabled(bool enabled)
    {
        // TODO
        (void)enabled; // To suppress unused-parameter warning.
    }

    void ContextWidget::set_context(const std::vector<ContextItem> &items)
    {
        // TODO
        (void)items; // To suppress unused-parameter warning.
    }

    void ContextWidget::clear_context()
    {
        // TODO
    }

    void ContextWidget::reset()
    {
        // TODO
    }

    void ContextWidget::request_context()
    {
        // TODO
    }

    void ContextWidget::budget_changed(int value)
    {
        // TODO
        (void)value; // To suppress unused-parameter warning.
    }

} // namespace aiws::gui
