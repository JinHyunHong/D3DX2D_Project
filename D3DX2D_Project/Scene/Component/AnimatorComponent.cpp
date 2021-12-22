#include "stdafx.h"
#include "AnimatorComponent.h"

AnimatorComponent::AnimatorComponent(Tool* const tool, Actor* const actor, 
	TransformComponent* const transform)  :
	IComponent(tool, actor, transform)
{
	timer = tool->GetManager<SubsystemManager>()->GetSubsystem<Timer>();
}

bool AnimatorComponent::Initialize()
{
	return true;
}

void AnimatorComponent::Update()
{
	if (current_animation.expired() || IsPlaying())
		return;

	frame_counter += timer->GetDeltaTimeMs();

	if (frame_counter > GetCurrentKeyFrame()->time)
	{
		current_frame_number++;

		switch (current_animation.lock()->GetRepeatType())
		{
		case RepeatType::Once:
		{
			if (current_frame_number >= current_animation.lock()->GetKeyFrameCount())
			{
				current_frame_number = current_animation.lock()->GetKeyFrameCount() - 1;
				Pause();
			}

			break;
		}
		case RepeatType::Loop:
		{
			current_frame_number %= current_animation.lock()->GetKeyFrameCount();
			break;
		}
		frame_counter = 0.0f;
		}
	}
}

void AnimatorComponent::Destroy()
{
	animations.clear();
}

auto AnimatorComponent::GetCurrentAnimation() const -> const std::shared_ptr<class Animation>
{
	return current_animation.expired() ? nullptr : current_animation.lock();
}

void AnimatorComponent::SetCurrentAnimation(const std::string& animation_name)
{
	assert(animations.find(animation_name) != animations.end());

	current_animation = animations[animation_name];
	current_frame_number = 0;
	frame_counter = 0.0f;
}

auto AnimatorComponent::GetCurrentKeyFrame() const -> const Keyframe* const
{
	assert(!current_animation.expired());
	return current_animation.lock()->GetKeyFrameFromIndex(current_frame_number);
}

void AnimatorComponent::AddAnimation(const std::string& animation_name, const std::shared_ptr<class Animation>& animation)
{
	assert(animations.find(animation_name) != animations.end());

	animations[animation_name] = animation;
}

void AnimatorComponent::AddAnimation(const std::string& path)
{
	auto resource_manager = tool->GetManager<ResourceManager>();
	auto animation = resource_manager->Load<Animation>(path);

	if (!animation)
		assert(false);

	AddAnimation(animation->GetResourceName(), animation);
}

void AnimatorComponent::Play()
{
	animation_mode = AnimationMode::Play;
	frame_counter = 0.0f;
}

void AnimatorComponent::Stop()
{
	animation_mode = AnimationMode::Stop;
	current_frame_number = 0;
	frame_counter = 0.0f;
}

void AnimatorComponent::Pause()
{
	animation_mode = AnimationMode::Pause;
}