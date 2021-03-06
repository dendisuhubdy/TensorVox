#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Voice.h"
#include <QStringList>
#include <QAudioFormat>
#include "voicemanager.h"
#include <QBuffer>
#include <QListWidgetItem>
#include <QAudio>
#include <QAudioOutput>
#include <queue>

#include "phonetichighlighter.h"

#include <QWinTaskbarButton>
#include <QWinTaskbarProgress>

#include "phoneticdict.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct InferDetails{
  QString Prompt;
  float Energy;
  float Speed;
  float F0;
  QListWidgetItem* pItem;
  int32_t SpeakerID;
  int32_t EmotionID;
  QString VoiceName;



};

typedef std::pair<uint32_t,size_t> InferIDTrueID;





class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    std::vector<InferIDTrueID> IdVec;
    VoiceManager VoMan;
    QAudioFormat StdFmt;
    QAudioOutput* StdOutput;

    QWinTaskbarButton* pTaskBtn;

    QWinTaskbarProgress* pTskProg;


    int32_t CurrentInferIndex;
    uint32_t CurrentAmtThreads;
    PhoneticDict PhonDict;

public:
    void* pDarkFw;
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
protected:
   void showEvent(QShowEvent *e) override;
public slots:
    void OnAudioRecv(std::vector<float> InDat,std::chrono::duration<double> infer_span,uint32_t inID);
    void OnAudioStateChange(QAudio::State newState);

private slots:
    void on_btnInfer_clicked();

    void on_btnLoad_clicked();

    void on_cbModels_currentIndexChanged(const QString &arg1);

    void on_sliEnergy_sliderMoved(int position);

    void on_sliSpeed_sliderMoved(int position);

    void on_lstUtts_itemDoubleClicked(QListWidgetItem *item);

    void on_btnClear_clicked();

    void on_btnExportSel_clicked();

    void on_actionExport_performance_report_triggered();

    void on_chkRecPerfLog_clicked(bool checked);

    void on_btnExReport_clicked();

    void on_btnRefreshList_clicked();

    void on_sliF0_sliderMoved(int position);

    void on_cbModels_currentTextChanged(const QString &arg1);

    void on_hkInfer_triggered();

    void on_actionOverrides_triggered();

    void on_actionRefresh_model_listing_triggered();

    void on_btnLoadInfo_clicked();

    void on_chkMultiThreaded_stateChanged(int arg1);

private:

    int32_t NumDone;
    int32_t GetID(int32_t InID);
    void SetDict();
    void HandleIsMultiSpeaker(size_t inVid);
    void HandleIsMultiEmotion(size_t inVid);
    bool CanPlayAudio;
    QStringList ListDirs(const QString& ParentDir);
    float RangeToFloat(int val);
    void PlayBuffer(QBuffer* pBuff,bool ByUser = false);
    bool RecPerfLines;

    void AdvanceBuffer();
    void AdvanceQueue();

    int32_t CountBlues();

    int32_t GetNumThreads();

    bool MustExplicitlyIterateQueue();
    void PopulateComboBox();

    std::vector<QBuffer*> AudBuffs;

    size_t CurrentBuffIndex;

    QStringList SuperWordSplit(const QString& InStr,int MaxLen);

    void ProcessCurlies(QString& ModTxt);


    std::queue<InferDetails> Infers;

    QStringList PerfReportLines;
    void IterateQueue();

    void DoInference(InferDetails &Dets);

    PhoneticHighlighter* pHigh;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
