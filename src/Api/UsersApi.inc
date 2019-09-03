<?php

declare(strict_types=1);

namespace SmashcastApi\Api;


use GuzzleHttp\Exception\GuzzleException;
use Psr\Http\Message\ResponseInterface;

class UsersApi extends AbstractApiBase
{
    /**
     * @throws GuzzleException
     */
    public function getUserByAuthToken(string $accessToken): ?string
    {
        $response = $this->apiGet('userfromtoken', ['authToken' => $accessToken]);
        $userData = json_decode($response->getBody()->getContents(), true);

        return $userData['user_name'] ?? null;
    }

    /**
     * @throws GuzzleException
     */
    public function getUserInfo(string $userId): ?array
    {
        $response = $this->apiGet("user/$userId");
        $userInfo = json_decode($response->getBody()->getContents(), true);
        return isset($userInfo['user_name']) ? $userInfo : null;
    }
}
