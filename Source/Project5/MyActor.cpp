#include "MyActor.h"
#include "Math/UnrealMathUtility.h" // FMath ����� ���� ���
#include "Engine/Engine.h"          // UE_LOG ���

// ������
AMyActor::AMyActor()
{
    // Tick �Լ� Ȱ��ȭ
    PrimaryActorTick.bCanEverTick = true;

    // ���� ��ġ �ʱ�ȭ
    Start = FVector2D(0.0f, 0.0f);
    PreviousPosition = Start;

    // �̵� �� �̺�Ʈ ���� ���� �ʱ�ȭ
    TotalDistance = 0.0f;
    TotalEventCount = 0;

    // Move�� �� ���� ȣ��ǵ��� ���� ���� ���� �ʱ�ȭ
    bHasMoved = false;
}

// BeginPlay: ���� ���� �� ȣ��
void AMyActor::BeginPlay()
{
    Super::BeginPlay();

    // Move �Լ� ȣ�� (��, �� ���� ȣ��ǵ��� bHasMoved�� ���� Ȯ��)
    if (!bHasMoved)
    {
        Move();
        bHasMoved = true;  // �� ���� ȣ��ǵ��� ���� ����
    }
}

// Tick: �� ������ ȣ��
void AMyActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Tick �Լ����� �߰����� �۾��� �ʿ��ϸ� ���⿡ �ۼ�
}

// Step �Լ�: 0 �Ǵ� 1�� ���� ��ȯ
int32 AMyActor::Step()
{
    return FMath::RandRange(0, 1);  // 0 �Ǵ� 1�� �����ϰ� ��ȯ
}

// �̺�Ʈ �߻� ���θ� �����ϴ� �Լ�
void AMyActor::TriggerEventWithProbability(float Probability)
{
    int32 RandomValue = FMath::RandRange(1, 100); // 1 ~ 100�� ���� ����
    if (RandomValue <= Probability)
    {
        TotalEventCount++;
        UE_LOG(LogTemp, Log, TEXT("Event Triggered!"));
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("Event Not Triggered"));
    }
}

// �� ��ǥ �� �Ÿ� ��� �Լ�
float AMyActor::CalculateDistance(FVector2D First, FVector2D Second)
{
    float dx = First.X - Second.X;
    float dy = First.Y - Second.Y;
    return FMath::Sqrt(dx * dx + dy * dy);  // �Ÿ� ���
}

// Move �Լ�: ĳ���͸� 10�� �����ϰ� �̵�
void AMyActor::Move()
{
    // 10ȸ �ݺ��Ͽ� �̵�
    for (int32 i = 0; i < 10; ++i)
    {
        // X�� Y �̵� �Ÿ� ����
        int32 DeltaX = Step();
        int32 DeltaY = Step();

        // ���� ��ġ�� �������� ���ο� ��ġ ���
        FVector2D NewPosition = Start + FVector2D(DeltaX, DeltaY);

        // �̵� �Ÿ� ��� (���� ��ġ�� �� ��ġ�� �Ÿ� ����)
        float Distance = CalculateDistance(PreviousPosition, NewPosition);
        TotalDistance += Distance;  // �� �̵� �Ÿ� ����

        // ��ǥ ������Ʈ
        Start = NewPosition;
        PreviousPosition = Start;

        // ���� ��ġ�� �̵� �Ÿ��� �α׷� ���
        UE_LOG(LogTemp, Warning, TEXT("Step %d: Moved to (%.1f, %.1f) | Distance: %.2f"), i + 1, Start.X, Start.Y, Distance);

        // �̺�Ʈ �߻� ���� Ȯ��
        TriggerEventWithProbability(50.0f);  // 50% Ȯ���� �̺�Ʈ �߻�

    }

    // �� �̵� �Ÿ��� �� �̺�Ʈ �߻� Ƚ�� ���
    UE_LOG(LogTemp, Log, TEXT("Total Distance: %.2f"), TotalDistance);
    UE_LOG(LogTemp, Log, TEXT("Total Events Triggered: %d"), TotalEventCount);
}
