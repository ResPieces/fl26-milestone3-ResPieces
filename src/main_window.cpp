#include "aiws/gui/main_window.hpp"

#include "aiws/gui/context_widget.hpp"
#include "aiws/gui/search_widget.hpp"
#include "aiws/gui/term_inspector_widget.hpp"
#include "aiws/gui/workspace_widget.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSplitter>
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>

namespace aiws::gui
{

    MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
    {
        setWindowTitle("AI Workspace");

        // Create the main widgets.
        workspace_widget_ = new WorkspaceWidget(this);
        search_widget_ = new SearchWidget(this);
        term_inspector_widget_ = new TermInspectorWidget(this);
        context_widget_ = new ContextWidget(this);

        reset_button_ = new QPushButton("Reset", this);
        exit_button_ = new QPushButton("Exit", this);
        status_label_ = new QLabel("Ready", this);

        auto *hlayout = new QHBoxLayout;
        hlayout->addWidget(term_inspector_widget_);
        hlayout->addWidget(context_widget_);

        auto *status = new QLabel("Current Status", this);
        QFont statusFont = status->font();
        statusFont.setBold(true);
        status->setFont(statusFont);

        auto *bottomlayout = new QHBoxLayout;
        bottomlayout->addWidget(status);
        bottomlayout->addWidget(status_label_);
        bottomlayout->addWidget(reset_button_);
        bottomlayout->addWidget(exit_button_);

        auto *main_layout = new QVBoxLayout;
        main_layout->addWidget(workspace_widget_, 2);
        main_layout->addWidget(search_widget_, 2);
        main_layout->addLayout(hlayout, 2);
        main_layout->addLayout(bottomlayout, 1);

        // resize(900, 900);
        // qDebug() << size();

        auto *central_widget = new QWidget(this);
        central_widget->setLayout(main_layout);
        setCentralWidget(central_widget);

        resize(900, 900);
        // qDebug() << size();

        // Connect widget events to MainWindow handlers.
        //
        // These signal names must match your widget header declarations.
        connect(workspace_widget_,
                &WorkspaceWidget::add_document_requested,
                this,
                &MainWindow::add_document);

        connect(workspace_widget_,
                &WorkspaceWidget::build_corpus_requested,
                this,
                &MainWindow::build_corpus);

        connect(workspace_widget_,
                &WorkspaceWidget::document_selected,
                this,
                &MainWindow::document_selected);

        connect(search_widget_,
                &SearchWidget::search_requested,
                this,
                &MainWindow::search_requested);

        connect(search_widget_,
                &SearchWidget::query_changed,
                this,
                &MainWindow::query_changed);

        connect(search_widget_,
                &SearchWidget::source_document_requested,
                this,
                &MainWindow::source_document_requested);

        connect(context_widget_,
                &ContextWidget::build_context_requested,
                this,
                &MainWindow::build_context_requested);

        connect(term_inspector_widget_,
                &TermInspectorWidget::term_inspection_requested,
                this,
                &MainWindow::term_inspection_requested);

        connect(reset_button_,
                &QPushButton::clicked,
                this,
                &MainWindow::reset_application);

        connect(exit_button_,
                &QPushButton::clicked,
                this,
                &MainWindow::exit_application);

        update_action_states();
    }

    void MainWindow::set_exit_callback(ExitCallback callback) noexcept
    {
        exit_callback_ = callback;
    }

    void MainWindow::add_document()
    {
        QString filePath = QFileDialog::getOpenFileName(
            this,
            "Add Document",
            QString(),
            "Text Files (*.txt)");

        if (filePath.isEmpty())
            return;

        QFile file(filePath);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "Failed to open:" << file.errorString();
            return;
        }

        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();

        QTextStream in(&file);
        QString fileContents = in.readAll();

        Document newDoc = Document(filePath.toStdString(), fileName.toStdString(), fileContents.toStdString());

        workspace_.add_document(newDoc);

        workspace_widget_->add_document(fileName);

        invalidate_corpus();
        update_action_states();
    }

    void MainWindow::build_corpus()
    {
        processing_core_.rebuild(workspace_);

        workspace_widget_->set_corpus_status("Corpus: Built");
        update_action_states();
    }

    void MainWindow::document_selected(int row)
    {
        const auto &documents = workspace_.documents();

        const auto &document = documents[row];

        workspace_widget_->show_selected_document(
            QString::fromStdString(document.title()),
            QString::fromStdString(document.text()));
    }

    void MainWindow::search_requested(const QString &query, int k)
    {
        // TODO
        (void)query; // To suppress unused-parameter warning.
        (void)k;     // To suppress unused-parameter warning.
    }

    void MainWindow::query_changed(const QString &query)
    {
        // TODO
        (void)query; // To suppress unused-parameter warning.
    }

    void MainWindow::build_context_requested(int token_budget)
    {
        // TODO
        (void)token_budget; // To suppress unused-parameter warning.
    }

    void MainWindow::source_document_requested(const QString &document_id)
    {
        // TODO
        (void)document_id; // To suppress unused-parameter warning.
    }

    void MainWindow::term_inspection_requested(const QString &term,
                                               const QString &chunk_id)
    {
        // TODO
        (void)term;     // To suppress unused-parameter warning.
        (void)chunk_id; // To suppress unused-parameter warning.
    }

    void MainWindow::reset_application()
    {
        // TODO
    }

    void MainWindow::exit_application()
    {
        // TODO
    }

    void MainWindow::update_action_states()
    {
        bool has_documents = !workspace_.documents().empty();

        workspace_widget_->set_build_corpus_enabled(has_documents);
    }

    void MainWindow::invalidate_corpus()
    {
        workspace_widget_->set_corpus_status("Corpus: Not Built");
        workspace_widget_->set_build_corpus_enabled(false);

        clear_processing_outputs();
    }

    void MainWindow::clear_processing_outputs()
    {
        workspace_widget_->clear_selected_document();
        search_widget_->reset();
        term_inspector_widget_->reset();
        context_widget_->reset();
    }

} // namespace aiws::gui
